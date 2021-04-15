#include "InternalLib.h"
#include <tuple>
#include <stack>

void InternalLib::PcompareStrings(std::vector<std::string>& vec) {
	std::vector<std::string> end;
	bool in = false;
	std::string tmp;
	for(size_t i = 0; i < vec.size(); ++i) {
		if(vec[i][0] == '\"') {
			end.push_back(tmp);
			tmp = "";
			in = true;
		}
		else if(vec[i][vec[i].size()-1] == '\"') {
			end.push_back(tmp);
			tmp = "";
			in = false;
		}
		
		if(!in) {
			end.push_back(vec[i]);
		}
		else {
			tmp += vec[i];
		}
	}
	vec = end;
}

void InternalLib::PcompareComments(std::vector<std::string>& vec, char commentCall) {
	bool in = false;
	bool done = false;
	std::vector<std::string> end;
	std::string tmp;
	for(size_t i = 0; i < vec.size(); ++i) {
		for(size_t j = 0; j < vec[i].size(); ++j) {
			if(vec[i][j] == '\n') {
				end.push_back(tmp);
				tmp = "";
				in = false;
				done = true;
			}
			if(vec[i][j] == commentCall && !in) {
				in = true;
				continue;
			}
			if(in) {
				tmp += vec[i][j];
			}
		}
		if(!done) {
			end.push_back(vec[i]);
		}
		done = false;
	}
	vec = end;
}

std::string InternalLib::vecToStr(std::vector<std::string> vec) {
	std::string ret;
	for(size_t i = 0; i < vec.size(); ++i) {
		ret += vec[i] + ",";
	}
	ret.erase(ret.begin()+(ret.size()-1));
	return ret;
}
std::string InternalLib::vecToStr(std::vector<int> vec) {
	std::string ret;
	for(size_t i = 0; i < vec.size(); ++i) {
		ret += vec[i] + ',';
	}
	ret.erase(ret.begin()+(ret.size()-1));
	return ret;
}
std::string InternalLib::vecToStr(std::vector<char> vec) {
	std::string ret;
	for(size_t i = 0; i < vec.size(); ++i) {
		ret += vec[i] + ',';
	}
	ret.erase(ret.begin()+(ret.size()-1));
	return ret;
}

InternalLib::Parser* InternalLib::Parser::addPlaceHolder(std::string to_replace, std::string replace) {
	args[to_replace] = replace;

	return this;
}
InternalLib::Parser* InternalLib::Parser::execute(std::string trigger, void(*fun)()) {
	args_exec[trigger] = fun;

	return this;
}
InternalLib::Parser* InternalLib::Parser::setIdents(char identStart, char identEnd) {
	this->identEnd = identEnd;
	this->identStart = identStart;

	return this;
}
std::string InternalLib::Parser::parse(std::string str) {
	std::string ret;
	std::string tmpStr;
	bool in;
	str += " ";
	for(size_t i = 0; i < str.length(); ++i) {
		if(str[i] == this->identStart) {
			in = true;
			++i; //skips the start
		}
		else if(str[i] == this->identEnd) {
			in = false;
			if(args_exec.count(tmpStr) > 1) {
				args_exec[tmpStr]();
			}
			else {
				ret += this->args[tmpStr] != "" ? this->args[tmpStr] : this->identStart + tmpStr + this->identEnd; //if there is no known arg called tmpStr, tmpStr will be added for later parsers or other works
			}
			tmpStr = "";
			++i; //skips the end
		}

		if(in) {
			tmpStr += str[i];
		}
		else {
			ret += str[i];
		}
	}
	return ret;
}

std::string InternalLib::sb(bool bool_) { //bool to string
	return bool_ ? "true" : "false";
}

bool InternalLib::between(float num, float min, float max) {
	return (num > min && num < max);
}

size_t InternalLib::searchForVal_i(tokenType str, std::string key) { //return the index in the str
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return i+2;
		}
	}
	throw ValueNotFoundError{};
	return -1;
}

std::string InternalLib::searchForVal(tokenType str, std::string key) {
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return str[i+2];
		}
	}
	throw ValueNotFoundError{};
	return "";
}

int InternalLib::random::randomint() {
	srand(time(NULL)%rand());
	return rand();
}

InternalLib::LangParser* InternalLib::LangParser::setFile(fs::path path) {
	this->path = path;
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::addCommand(Command com) {
	com.argPref = this->argPrefix;
	
	commands.push_back(com);
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::setArgPrefix(char pref) {
	for(size_t i = 0; i < commands.size(); ++i) {
		commands[i].setArgPrefix(pref);
	}
	this->argPrefix = pref;
	return this;
}

InternalLib::LangParser::Command* InternalLib::LangParser::Command::setArgPrefix(char pref) {
	for(size_t i = 0; i < args.size(); ++i) {
		args[i].pref = pref;
	}
	this->argPref = pref;
	return this;
}

InternalLib::LangParser::Command* InternalLib::LangParser::Command::addArg(Arg arg) {
	arg.pref = this->argPref;

	args.push_back(arg);
	return this;
}

InternalLib::LangParser::Command* InternalLib::LangParser::Command::setName(std::string name) {
	this->name = name;
	return this;
}

InternalLib::LangParser::Command::Arg* InternalLib::LangParser::Command::Arg::setType(type ty) {
	if(ty == type::ATAG) {
		sgetFun([](Arg& arg, tokenType& tokens, Register& vars, size_t& pos, const std::vector<Handlers::Operator>& operators,LangParser* parser) {
			arg.setEntry("1");
		});
	}
	this->ty = ty;
	return this;
}

InternalLib::LangParser::Command::Arg* InternalLib::LangParser::Command::Arg::setName(std::string name) {
	this->name = name;
	return this;
}

void InternalLib::LangParser::Command::trigger(tokenType& tokens,Register& vars, size_t& pos, const std::vector<Handlers::Operator>& operators,LangParser* parser) {
	tokens.erase(tokens.begin()); //deleting the command name
	bool breakof = false;
	DEBUG_MESSAGE("tokensize: " << tokens.size())
	for(size_t i = pos; i < tokens.size(); ++i) {
		if(tokens[i] == "\n") {
			pos = i;
			DEBUG_MESSAGE("i is now:" << i)
			goto END;
		}
		DEBUG_MESSAGE("start loop with " << tokens[i])
		DEBUG_MESSAGE("checking for \"" << tokens[i][0] << "\" == \"" << this->argPref << "\"")
		if(tokens[i][0] == this->argPref) {
			std::string str = tokens[i];
			str.erase(str.begin()); //deletes the prefix
			for(size_t j = 0; j < args.size(); ++j) {
				if(args[j].ty == Arg::AGET) {
					DEBUG_MESSAGE("found AGET")
					continue;
				}
				if(args[j].registerEntry != "") {
					DEBUG_MESSAGE("skiped because of reused entry of " << args[j].registerEntry)
					continue;
				}
				DEBUG_MESSAGE("info about current arg: name=" << args[j].name << "; typ=" << (args[j].ty == Arg::type::ATAG ? "ATAG" : "ASET") << "; prefix=" << args[j].pref  )
				if(str == args[j].name) {
					if(args[j].ty == Arg::type::ASET) {
						DEBUG_MESSAGE("found ASET that maches with " << argPref << str)
						size_t k = i+1;
						args[j].getFun(args[j],tokens,vars,k,operators,parser);
						i=k;
						DEBUG_MESSAGE("skips [" << tokens[i] << "]")
					}
					else {
						DEBUG_MESSAGE("found ATAG that maches with " << argPref << str)
						args[j].getFun(args[j],tokens,vars,i,operators,parser);
					}
					
					DEBUG_MESSAGE("set " << args[j].name << " to " << args[j].registerEntry)

					regis[args[j].name] = args[j].registerEntry;
					break;
				}
			}
		}
		else {
			for(size_t j = 0; j < args.size(); ++j) { 		
				if(args[j].registerEntry != "") {
					DEBUG_MESSAGE("skiped because of reused entry of " << args[j].registerEntry)
					continue;
				}
				if(args[j].ty != Arg::AGET) {
					continue;
				}
				DEBUG_MESSAGE("found AGET arg named " << args[j].name)
				args[j].getFun(args[j],tokens,vars,i,operators,parser);
				DEBUG_MESSAGE("set regis[" << args[j].name << "] to " << args[j].registerEntry)
				this->regis[args[j].name] = args[j].registerEntry;
				break;
				
			}
		}
		if(i+1 >= tokens.size()) {
			pos = i;
			DEBUG_MESSAGE("i:" << i)
		}
	}
	END:
	DEBUG_MESSAGE("run current Command");
	this->fun(this,vars,regis,parser);
	DEBUG_MESSAGE("clear register");
	this->regis.clear();
	
	for(size_t i = 0; i < args.size(); ++i) {
		args[i].registerEntry = "";
	}
}

#define clearOut(tokens, cha, tmpVar ) \
	while(tmpVar) { \
		tmpVar = false; \
		for(size_t i = 0; i < tokens.size(); ++i) { \
			if(allCharactersSame(tokens[i],cha)) { \
				tokens.erase(tokens.begin()+i); \
				DEBUG_MESSAGE("found a \"" << cha << "\" and deleted it") \
				tmpVar = true; \
			} \
		} \
	} \

InternalLib::Register InternalLib::LangParser::parse(std::string str, bool main, Register additionalRegister) {
	if(stoping) {
		return variableRegister;
	}
	tokenType tokens = InternalFsys::splitTokens(" ",str);
	
	DEBUG_MESSAGE("tokens after split1: " << InternalLib::vecToStr(tokens))
	for(size_t i = 0; i < tokens.size(); ++i) { //splits the tokens for every "\n", but keeps it
		DEBUG_MESSAGE("starts loop to skip \\n [i:" << i << "]")
		std::string tmp = "";
		std::string tmp2 = "";
		for(size_t j = 0; j < tokens[i].size(); ++j) {
			if(tokens[i][j] == '\n') {
				for(size_t k = j+1; k < tokens[i].size(); ++k) {
					tmp2 += tokens[i][k];
				}
				DEBUG_MESSAGE("going to delete: \"" << tokens[i] << "\"")
				tokens.erase(tokens.begin()+i);
				DEBUG_MESSAGE("replace it with: {" << tmp << ",\\n," << tmp2 << "}")
				tokens.insert(tokens.begin()+i,tmp2);
				DEBUG_MESSAGE("tokens[" <<i << "] is now: " << tokens[i])
				tokens.insert(tokens.begin()+i,"\n");
				DEBUG_MESSAGE("tokens[" <<i << "] is now: " << tokens[i])
				tokens.insert(tokens.begin()+i,tmp);
				DEBUG_MESSAGE("tokens[" <<i << "] is now: " << tokens[i])
				++i;
				tmp = "";
				tmp2 = "";
			}
			else {
				tmp += tokens[i][j];
			}
		}
	}
	pos = nullptr;
	DEBUG_MESSAGE("tokens after split2: " << InternalLib::vecToStr(tokens))
	//InternalLib::PcompareStrings(tokens); // deal with the " parsing
	//InternalLib::PcompareComments(tokens,this->comment); // deal with the comments-parsing
	bool found = true;
	while(found) { //clears every " " in the tokens
		found = false;
		for(size_t i = 0; i < tokens.size(); ++i) {
			if(allCharactersSame(tokens[i],' ')) {
				tokens.erase(tokens.begin()+i);
				DEBUG_MESSAGE("found a \" \" and deleted it")
				found = true;
			}
		}
	}
	DEBUG_MESSAGE("tokens after split3: " << InternalLib::vecToStr(tokens))
	tokens = Handlers::stickSameChar(tokens,'\"',{' ', '\n', '\0', '\r'});
	tokens = Handlers::stick4(tokens,'{','}', {' ', '\n', '\0', '\r'});
	//tokens = Handlers::stick4(tokens,'"','"', {' ', '\n', '\0', '\r'});
	tokens = Handlers::stick4(tokens,'(',')', {' ', '\n', '\0', '\r'});
	tokens = Handlers::stick4(tokens,'[',']', {' ', '\n', '\0', '\r'});
	DEBUG_MESSAGE("tokens after split4: " << InternalLib::vecToStr(tokens))

	size_t count = 0;
	for(size_t i = 0; i < tokens.size(); ++i) {
		if(tokens[i] == "\n") {
			++count;
			lineRegister[count] = i-2;
		}
	}
	variableRegister["__file__"] = path.string() != "" ? path.string() : "__unknown__" ;
	variableRegister["__username__"] = System::getSysUsername_s();
	variableRegister["__main__"] = main ? "1":"0";
	variableRegister["__start_time__"] = std::to_string(time(NULL));

	variableRegister.insert(additionalRegister.begin(),additionalRegister.end());

	DEBUG_MESSAGE("token size:" << tokens.size())
	for(size_t i = 0; i < tokens.size(); ++i) {
		pos = &i;
		if(lineRegister.count(i) != 0) {
			variableRegister["__line__"] = std::to_string(lineRegister[i]);
		}
		
		int notFoundCounter = 0;
		if(isIn(tokens[i],{"\n","\r"," ",""})) {
			continue;
		}
		for(size_t j = 0; j < commands.size(); ++j) {
			DEBUG_MESSAGE("check for " << commands[j].name << " == " << tokens[i])
			
			if(tokens[i][0] == argPrefix) {
				DEBUG_MESSAGE("broke because of checking an argument [" << tokens[i] << "]")
				throw SyntaxError{};
				break;
			}
			else if(allCharactersSame(tokens[i],'\n')) {
				DEBUG_MESSAGE("skips a \\n at i:" << i)
				continue;
			}
			else if(commands[j].name == tokens[i]) {
				DEBUG_MESSAGE("success by checking")
				commands[j].trigger(tokens,this->variableRegister,i,operators,this);
				//--i;
				break;
			}
			else {
				notFoundCounter += 1;

				if(notFoundCounter == commands.size()) {
					throw CommandNotFoundError{};
					break;
				}
				continue;
			}
		}
		if(stoping) {
			goto END_;
		}
	}
	END_:
	return variableRegister;
	/*
	InternalErrLog::LogMain.append(time(NULL),SyntaxError{}.toString());
	throw SyntaxError{};
	*/

}

InternalLib::LangParser* InternalLib::LangParser::parse() {
	DEBUG_MESSAGE("start lang parse with " << path.string())
	DEBUG_MESSAGE("read = \"\n" << InternalFsys::readNormal(this->path.string()) << "\n\"")
	parse(InternalFsys::readNormal(this->path.string()));
	return this;
}

InternalLib::LangParser::Command::Arg* InternalLib::LangParser::Command::Arg::setEntry(std::string entry) {
	this->registerEntry = entry;
	return this;
}

InternalLib::LangParser::Command* InternalLib::LangParser::Command::setExecute(executeFunction fun) {
	this->fun = fun;
	return this;
}

InternalLib::LangParser::Command::Arg* InternalLib::LangParser::Command::Arg::sgetFun(getFunction func) {
	if(ty == ATAG) {
		InternalErrLog::LogMain.append(time(NULL),ParserTagCantHaveAGetFunctionError{}.toString());
		//throw ParserTagCantHaveAGetFunctionError{};
	}

	this->getFun = func;
	return this;
}

InternalLib::LangParser::Command::Arg& InternalLib::LangParser::Command::getByName(std::string name) {
	for(size_t i = 0; i < args.size(); ++i) {
		if(args[i].name == name) {
			return args[i];
		}
	}
	InternalErrLog::LogMain.append(time(NULL),ValueNotFoundError{}.toString());
	throw ValueNotFoundError{};
}

InternalLib::LangParser InternalLib::LangParser::toInstance() {
	LangParser ret;
	ret.setArgPrefix(this->argPrefix)
	->setComment(this->comment)
	->setFile(this->path)
	->setArgPrefix(argPrefix)
	->addOperators(operators)
	->enableStandards(this->features)
	->variableRegister = variableRegister;
	ret.commands = this->commands;

	return ret;
}
InternalLib::LangParser::Command InternalLib::LangParser::Command::toInstance() {
	Command ret;
	ret.setExecute(this->fun)
	->setName(this->name)
	->setArgPrefix(this->argPref)
	->args = this->args;

	return ret;
}
InternalLib::LangParser::Command::Arg InternalLib::LangParser::Command::Arg::toInstance() {
	Arg ret;
	ret.setName(this->name)
	->setEntry(this->registerEntry)
	->sgetFun(this->getFun)
	->setType(this->ty)
	->pref = this->pref;

	return ret;
}

InternalLib::LangParser* InternalLib::LangParser::setComment(char comment) {
	this->comment = comment;
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::include(const LangParser& pars) {
	for(size_t i = 0; i < pars.commands.size(); ++i) {
		this->commands.push_back(pars.commands[i]);
	}
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::off() {
	this->stoping = true;
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::unlock() {
	this->stoping = false;
	return this;
}

bool InternalLib::allCharactersSame(std::string s, char it) {
    for (size_t i = 0; i < s.length(); ++i)
        if (s[i] != it)
            return false;
    
    return true;
}

InternalLib::LangParser* InternalLib::LangParser::addOperator(Handlers::Operator operat) {
	DEBUG_MESSAGE("pushing back operator named: " << operat.getName())
	this->operators.push_back(operat);
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::addOperators(std::vector<Handlers::Operator> operators) {
	for(size_t i = 0; i < operators.size(); ++i) {
		this->operators.push_back(operators[i]);
	}
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::setVariableCall(char call) {
	this->variablecall = call;
	return this;
}

void InternalLib::Handlers::CommandStorage::run(tokenType& tokens, size_t& pos, const std::vector<Handlers::Operator>& operators,LangParser* parser) {
	for(size_t i = 0; i < commands.size(); ++i) {
		commands[i].trigger(tokens,reg,pos,operators,parser);
	}
}
	
bool InternalLib::Handlers::CommandStorage::empty() const {
	return commands.size() == 0 && arguments.size() == 0;
}


InternalLib::Register InternalLib::Handlers::handleSwiftCRegister(std::string full) {
	tokenType tokens = InternalFsys::splitTokens(" |\n|",full);
	
	InternalLib::Register ret;	
	if(tokens.size() % 3 != 0 ) { //cant be a Register because it doesn't fit in the { key : val ... } prinzip 
		throw SyntaxError{};
	}

	for(size_t i = 0; i < tokens.size(); i+=3) {
		if(tokens[i+1] != ":") {
			throw SyntaxError{};
		}
		
		ret[tokens[i]] = tokens[i+2];
	}
	return ret;
}

InternalLib::Handlers::CommandStorage InternalLib::Handlers::handleSwiftCCommandVector(std::string full, const std::vector<InternalLib::LangParser::Command>& commands, InternalLib::Register& regist) { //returns the commands and the argument list for the current command (Node: it isn't allowed to use multi-line-operating commands like if or loop in these kind of thing because you cant acces the next command) will be fixed later!
	tokenType tokens = InternalFsys::splitTokens(" ",full);

	for(size_t i = 0; i < tokens.size(); ++i) { //loops through the vector and splits the tokens after a \n. so that {command\ncommand\ncommand...} without spaces between command and \n can run
		std::string tmpStr = "";
		std::string tmpStr2 = "";
		for(size_t j = 0; j < tokens[i].size(); ++i) {
			tmpStr += tokens[i][j];
			if(tokens[i][j] == '\n') {
				break;
				tmpStr2 = tokens[i].substr(tmpStr.size()-1,tokens[i].size()-1);
			}
		}
		if(tmpStr2 != "") {
			tokens.erase(tokens.begin()+i);
			tokens.push_back(tmpStr);
			tokens.push_back(tmpStr2);
			++i;
		}

	}

	bool found = false;
	std::vector<InternalLib::LangParser::Command> retCom;
	std::vector<std::vector<std::string>> retStr;

	for(size_t i = 0; i < tokens.size(); ++i) {
		for(size_t j = 0; j < commands.size(); ++j) {
			if(commands[j].name == tokens[i]) {
				retCom.push_back(commands[j]);
				found = true;
				std::string tmp;
				std::vector<std::string> tmpVec;
				for(size_t k = 0; tokens[i].size(); ++k) {
					if(tokens[i][k] == '\n') {
						tmpVec.push_back(tmp);
						tmp = "";
						break;
					}
					tmp += tokens[i][k];
				}
				retStr.push_back(tmpVec);
				break; //command found
			}	
		}
		if(!found) {
			throw SyntaxError{};
		}
		found = false;
	}
	return CommandStorage(retCom,retStr,regist); //command,arguments,register
}

std::vector<std::string> InternalLib::Handlers::handleSwiftCVector(std::string full) {
	return InternalFsys::splitTokens(",",full);
}

std::tuple<InternalLib::Handlers::CommandStorage,std::vector<std::string>,InternalLib::Register,InternalLib::Handlers::returnType> InternalLib::Handlers::handleSwiftC(std::string full,const std::vector<InternalLib::LangParser::Command>& commands,InternalLib::Register& regist) {
	full.erase(full.begin());	//delete the {
	full.erase(full.begin() + full.size()-1); //delete the }
	CommandStorage retVecCom; //tuple of commands and arguments
	std::vector<std::string> retVecStr;
	InternalLib::Register retReg;
	returnType retT;
	
	//tokenType tokens = InternalFsys::splitTokens(",",full);
	tokenType tokens = InternalFsys::splitTokens(" ",full);
	if(
	[&]()->bool {
		for(size_t i = 0; i < commands.size(); ++i) {
			if(commands[i].name == tokens[0]) { //tokens[0] is a command
				return true;
			}
		}
		return false;
	      }()
	) {
		retVecCom = handleSwiftCCommandVector(full,commands,regist);
		retT = returnType::Command;
	}
	else if(full[0] == '\"' /*the first element is a string*/ || isInt(InternalFsys::splitTokens(",",full)[0]) /* the first element is a string*/ ) {
		retVecStr = handleSwiftCVector(full);
		retT = returnType::Vector;
	}
	else if(InternalFsys::splitTokens(" ",full)[1] == ":") {
		retReg = handleSwiftCRegister(full);
		retT = returnType::Register;
	}

	return std::tuple<InternalLib::Handlers::CommandStorage,std::vector<std::string>,InternalLib::Register,InternalLib::Handlers::returnType>(retVecCom,retVecStr,retReg,retT);
}


//handler for expressions


std::string InternalLib::Handlers::Operator::getName() const {
	return name;
}

bool InternalLib::isInt(std::string str) {
	try {
		std::stoi(str);
	}
	catch(...) {
		return false;
	}
	return true;
}

int InternalLib::Handlers::handleExpression(std::string expr,const std::vector<Operator>& operators, char variablecall, Register& vars) {
	DEBUG_MESSAGE("operator-size: " << operators.size())
	
	int tmp = 0;
	bool found = false;
	tokenType tokens = InternalFsys::splitTokens(" ",expr);
	for(size_t i = 0; i < tokens.size(); ++i) {
		if(isIn(tokens[i],{" ","","\n","\r"})) {
			tokens.erase(tokens.begin()+i);
			--i;
		}
	}
	if(tokens.size() == 1 && ( isInt(tokens[0]) || checkvariable(variablecall,tokens[0],vars) != tokens[0])) {
		DEBUG_MESSAGE("tokens.size() == 1! tokens[0]: " << tokens[0])
		return std::stoi(checkvariable(variablecall,tokens[0],vars));
	}

	tokens = stick4(tokens,'(',')',{' ','\n','\r','\0'});
	DEBUG_MESSAGE("full: " << IL::vecToStr(tokens));
	for(size_t i = 1; i < tokens.size(); ++i) {
		DEBUG_MESSAGE("loop in expr with: " << tokens[i])
		if(tokens[i] == "") {
			continue;
		}
		if(i == 1) {
			if(tokens[0][0] == '(') {
				tmp = handleNormalBexpr(tokens[0],operators,variablecall,vars);
			}
			else {
				tmp = std::stoi(Handlers::checkvariable(variablecall,tokens[0],vars));
			}
			DEBUG_MESSAGE("i is 1! tmp is now: " << tmp)
		}
		std::string str;
		int int_;
		try {
			auto [ int__, str_ ] = checkNormalBexpr(tokens[i+1],operators,variablecall,vars);
			DEBUG_MESSAGE("int: " << int__ << " str: \"" << str << "\"")
			int_ = int__;
			str = str_;
		}
		catch(std::logic_error& err) {
			DEBUG_MESSAGE("ERROR LOL")
		}
		

		for(size_t j = 0; j < operators.size(); ++j) {
			while(isIn(tokens[i][tokens[i].size()-1],{' ','\n','\r','\0'})) {
				DEBUG_MESSAGE("erased \"" << tokens[i][tokens.size()-1] << "\"");
				tokens[i].erase(tokens[i].begin()+tokens[i].size()-1);
			}
			while(isIn(tokens[i][0],{' ','\n','\r','\0'})) {
				DEBUG_MESSAGE("erased " << tokens[i][0]);
				tokens[i].erase(tokens[i].begin());
			}

			DEBUG_MESSAGE("checking for \"" << operators[j].getName() << "\" == \"" << tokens[i] << "\"")
			if(operators[j].getName() == tokens[i]) {
				if(str == "FALSE") {
					DEBUG_MESSAGE("str is FALSE!")
					tmp = operators[j].executeFun(tmp,int_);
					++i;
				}
				else {
					DEBUG_MESSAGE("x")
					DEBUG_MESSAGE("tmp = executeFun(" << tmp << ",std::stoi(" << tokens[i+1] << "))")
					tmp = operators[j].executeFun(tmp,std::stoi(checkvariable(variablecall,tokens[i+1],vars)));
					i+=1;
				}
				DEBUG_MESSAGE("tmp is now: " << tmp )
				
				
				found = true;
			}
		}
		if(!found) {
			throw ExpressionSyntaxError{};
		}
		found = false;
	}
	return tmp;
}


//handler for ( and )

int InternalLib::Handlers::handleNormalBexpr(std::string str,const std::vector<Operator>& operators, char variablecall,Register& vars) {
	DEBUG_MESSAGE("input: " << str)
	size_t i = 0;
	while(isIn(str[i],{' ','\n','\r','\0'})) {
		if(i+1 >= str.size()) {
			throw BracesMisMatchError{};
		}
		++i;
	}
	size_t j = str.size()-1;
	while(isIn(str[j],{' ','\n','\r','\0'})) {
		if(j-1 <= 0) {
			throw BracesMisMatchError{};
		}
		--j;
	}
	DEBUG_MESSAGE("handleExpresion with \"" << str.substr(i+2,j-2) << "\" [i:" << i << "|j:" << j << "]")
	return handleExpression(str.substr(i+2,j-2),operators,variablecall,vars);
}

std::tuple<int,std::string> InternalLib::Handlers::checkNormalBexpr(std::string str, const std::vector<Operator>& operators, char variablecall, Register& vars) {
	if(str[0] == '(' && str[str.size()-1] == ')') {
		return std::tuple<int,std::string>(handleNormalBexpr(str,operators,variablecall,vars),"FALSE");
	}
	return std::tuple<int,std::string>(0,str);
}

//handler for variables

std::string InternalLib::Handlers::handleVariablesGet(std::string full, InternalLib::Register& reg) {
	DEBUG_MESSAGE("triggerd handleVariablesGet with " << full)
	if(reg.count(full) == 0) {
		throw VariableAccessError{};
	}

	return reg[full];
}
void InternalLib::Handlers::handleVariablesSet(std::string full, InternalLib::Register& reg, std::string set) {
	reg[full] = set;
}
std::string InternalLib::Handlers::checkvariable(char call, std::string check, InternalLib::Register& reg) {
	if(check[0] == call) {
		check.erase(check.begin());
		return handleVariablesGet(check.substr(0,check.size()),reg);
	}
	return check;
}


//pre interpreter


void InternalLib::Handlers::preInterpreter::preInterpret(InternalLib::Register& GVA, const std::vector<InternalLib::LangParser::Command>& commands, tokenType tokens) {
	GVA["__PRE__"] = "1";
	for(size_t i = 0; i < tokens.size(); ++i) {
		
	}
	GVA["__PRE__"] = "0"; 
}

std::string InternalLib::makeUUID() {
	srand(time(NULL));
	return std::to_string(rand()) + "." + std::to_string(rand()) + "." + std::to_string(rand()) + "." + std::to_string(time(NULL));
}

tokenType InternalLib::Handlers::stick4(const tokenType& tokens, const char begin, const char end, const std::vector<char> ignore) {
	std::stack<char> bgen;
	tokenType endTokens;
	int founds = 0;
	std::string tmp;
	STATIC_MASSERT(end != begin)
	for(size_t i = 0; i < tokens.size(); ++i) {
		for(size_t j = 0; j < tokens[i].size(); ++j) {
			if(IL::isIn(tokens[i][j],ignore)) {
				continue;
			}
			else {
				if(tokens[i][j] == begin) {
					++founds;
					bgen.push(begin);
				}
				else if(tokens[i][j] == end) {
					--founds;
					if(bgen.empty()) {
						throw BracesMisMatchError{};
					}
					bgen.pop();
					
					if(bgen.empty()) {
						tmp += " ";
						tmp += end;
						tmp.erase(tmp.begin());
						endTokens.push_back(tmp);
						tmp = "";
						if(i+1 >= tokens.size()) {
							goto END;
						}
						else {
							++i;
						}
					}

					
				}
				break;
			}
		}
		if(bgen.empty()) {
			//if(endF) {
			//	endTokens.push_back(tokens[i]);
			//}
			endTokens.push_back(tokens[i]);
		}
		else {
			tmp += " " + tokens[i];
		}
	}
	END:
	if(!bgen.empty() /*|| founds != 0*/) {
		throw BracesMisMatchError{};
	}
	return endTokens;
}

tokenType InternalLib::Handlers::stickSameChar(const tokenType& tokens, const char ch, const std::vector<char> ignore) {
	DEBUG_MESSAGE("input: " << InternalLib::vecToStr(tokens))
	bool in = false;
	tokenType endTokens;
	int founds = 0;
	std::string tmp;
	for(size_t i = 0; i < tokens.size(); ++i) {
		DEBUG_MESSAGE(i << ":" << tokens[i])
		for(size_t j = 0; j < tokens[i].size(); ++j) {
			DEBUG_MESSAGE("checks with \"" << tokens[i][j] << "\"")
			if(IL::isIn(tokens[i][j],ignore)) {
				continue;
			}
			if(tokens[i][j] == ch && !in) {
				DEBUG_MESSAGE("in")
				in = true;
			}
			else if(tokens[i][tokens[i].size()-1] == ch && in) {
				DEBUG_MESSAGE("out")
				in = false;
				tmp.erase(tmp.begin());
				DEBUG_MESSAGE("tmp:" << tmp)
				endTokens.push_back(tmp + " " + tokens[i]);
				tmp = "";
				if(i+1 >= tokens.size()) {
					DEBUG_MESSAGE("end jmp")
					goto END;
				}
				else {
					++i;
				}	
			}
			break;
		}
		
		if(!in) {
			endTokens.push_back(tokens[i]);
		}
		else {
			tmp += " " + tokens[i];
		}
	}
	END:
	if(in) {
		//throw BracesMisMatchError{};
	}
	DEBUG_MESSAGE("out:" << InternalLib::vecToStr(endTokens))
	return endTokens;

}

InternalLib::LangParser* InternalLib::LangParser::enableStandard(standardFeature feature) {
	try {
		if(isIn(feature,features)) {
			return this;
		}
		size_t index = IL::lastOfarray(this->features,standardFeature::EMPTY);
		this->features[index] = feature;
	}
	catch(ValueNotFoundError& err) {
		throw ArrayOutOfRangeError{};
	}
	return this;
}

InternalLib::LangParser* InternalLib::LangParser::enableStandards(standardFeature features[]) {
	for(size_t i = 0; i < (sizeof(features)/sizeof(standardFeature)); ++i) {
		this->enableStandard(features[i]);
	}
	return this;
}

void InternalLib::LangParser::executeStandardFeatures() {
	for(size_t i = 0; i < (sizeof(this->features)/sizeof(standardFeature)); ++i) {
		switch(features[i]) {
			using s = standardFeature;
		case s::EMPTY: 
			continue;
			break;
		case s::standardComments:
			this->comment = ';';
			break;
		case s::standardSTDLibPath:

			break;
		default:
			break;
		}
	}
}

InternalLib::LangParser* InternalLib::LangParser::linkStdlibDir(fs::path dir) {
	this->pathToStdlib = path;
	return this;
}