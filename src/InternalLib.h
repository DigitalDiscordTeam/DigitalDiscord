#ifndef INTERNAL_LIB_H
#define INTERNAL_LIB_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalFsys.h"
#include "InternalSys.h"

#include <string>
#include <vector>
#include <map>

namespace InternalLib {
    template<typename type>
    size_t inline lastOfarray(type array[],type emptySlot) {
        for(size_t i = 0; i < (sizeof(array)/sizeof(type)); ++i) {
            if(array[i] == emptySlot) {
                return i;
            }
        }
        throw ValueNotFoundError{};
        return -1;
    }
    std::string makeUUID();

    bool isInt(std::string str);

    template<typename type>
    inline bool isIn(const type& t, const std::vector<type>& vec) {
        for(size_t i = 0; i < vec.size(); ++i) {
            if(vec[i] == t) {
                return true;
            }
        }
        return false;
    }
    template<typename type>
    inline bool isIn(const type t, type array[]) {
        for(size_t i = 0; i < (sizeof(array)/sizeof(type)); ++i) {
            if(array[i] == t) {
                return true;
            }
        }
        return false;
    }


    void PcompareStrings(std::vector<std::string>& vec);
    void PcompareComments(std::vector<std::string>& vec, char commentCall);

    std::string vecToStr(std::vector<std::string> vec);
    std::string vecToStr(std::vector<int> vec);
    std::string vecToStr(std::vector<char> vec);

	class Parser {
		std::map<std::string,std::string> args;
		char identStart;
		char identEnd;
        std::map<std::string,void(*)()> args_exec;
	public:
		Parser* addPlaceHolder(std::string to_replace, std::string replace);
		Parser* setIdents(char identStart, char identEnd);
        Parser* execute(std::string trigger, void(*fun)());
		std::string parse(std::string str);
	};

    namespace Handlers {
        class Operator;
    }
    using Register = std::map<std::string,std::string>;
    class LangParser {
        bool stoping = false;
    public:
        fs::path pathToStdlib = fs::path();
        size_t* pos = nullptr;
        std::map<size_t,size_t> lineRegister; // line - pos
        Register variableRegister;
        class Command {
        public:
            class Arg {
            public:
                using getFunction = void(*)(LangParser::Command::Arg&,tokenType& tokens,Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, LangParser* parser);
                using executeFunction = void(*)(LangParser::Command* com,Register& vars,Register& entry, LangParser* parser);
                enum type {
                    AGET, //no prefix needed, get only the input
                    ASET, //prefix needed, for example : -<name> <value>
                    ATAG  //no argument given, used for tags
                };
                type ty;
                char pref = 0;
                std::string name;
                std::string registerEntry = ""; //stores the last register entry
                getFunction(getFun);

                Arg* setType(type ty);
                Arg* setName(std::string name);
                Arg* setEntry(std::string entry);
                Arg* sgetFun(getFunction func);
                Arg toInstance();
                
            };
            using getFunction = Arg::getFunction;
            using executeFunction = Arg::executeFunction;
            Register regis; //stors the return values of the arguments (will be cleared after end of trigger())
            executeFunction fun;
            std::string name;
            char argPref = 0;
            std::vector<Arg> args;

            Command* setArgPrefix(char pref);
            Command* addArg(Arg arg);
            Command* setName(std::string name);
            Command toInstance();
            Command* setExecute(executeFunction fun);

            void trigger(tokenType& tokens,Register& vars, size_t& pos, const std::vector<Handlers::Operator>& operators,LangParser* parser);
            Arg& getByName(std::string name);
            
        };
        using getFunction = Command::getFunction;
        using executeFunction = Command::executeFunction;
        fs::path path;
        std::vector<Command> commands;
        std::vector<Handlers::Operator> operators;
        char argPrefix = 0;
        char comment = 0;
        char variablecall = '$';

        LangParser* setFile(fs::path path); 
        LangParser* addCommand(Command com);
        LangParser* setArgPrefix(char pref);
        Register parse(std::string str, bool main = true, Register additionalRegister = Register());
        LangParser* parse();
        LangParser toInstance();
        LangParser* setComment(char comment);
        LangParser* include(const LangParser& pars);
        LangParser* addOperator(Handlers::Operator operat);
        LangParser* addOperators(std::vector<Handlers::Operator> operators);
        LangParser* setVariableCall(char call);
        LangParser* off();
        LangParser* unlock();
        LangParser* linkStdlibDir(fs::path dir);
        //LangParser* include(STDCOM com);
        
        enum class standardFeature {
            autoVariables,
            autoExpression,
            allStandardLibraries,
            allStandardOperators,
            standardComments,
            standardSTDLibPath,
            EMPTY
        };
        LangParser* enableStandard(standardFeature feature);
        LangParser* enableStandards(standardFeature features[]);
        standardFeature features[6] = {
            standardFeature::EMPTY,
            standardFeature::EMPTY,
            standardFeature::EMPTY,
            standardFeature::EMPTY,
            standardFeature::EMPTY,
        };
        void executeStandardFeatures();
    };

    namespace Handlers {
        tokenType stick4(const tokenType& tokens, const char begin, const char end, const std::vector<char> ignore);
        class CommandStorage {
        public:
            std::vector<InternalLib::LangParser::Command> commands;
            std::vector<std::vector<std::string>> arguments;
            InternalLib::Register reg;

            void run(tokenType& tokens, size_t& pos, const std::vector<Handlers::Operator>& operators,LangParser* parser);
            
            bool empty() const;
            
            CommandStorage(std::vector<InternalLib::LangParser::Command> commands,std::vector<std::vector<std::string>> arguments,InternalLib::Register reg) : commands(commands), arguments(arguments), reg(reg)  {}
            CommandStorage() {}
        };

        InternalLib::Register handleSwiftCRegister(std::string full);

        CommandStorage handleSwiftCCommandVector(std::string full, const std::vector<InternalLib::LangParser::Command>& commands, InternalLib::Register& regist);

        std::vector<std::string> handleSwiftCVector(std::string full);

        enum class returnType {
            Command, //function will return a Command-list
            Vector,	//function will return a vector
            Register //function will return a Register
        };

        std::tuple<CommandStorage,std::vector<std::string>,InternalLib::Register,returnType> handleSwiftC(std::string full,const std::vector<InternalLib::LangParser::Command>& commands,InternalLib::Register& regist);


        //handler for expressions

        class Operator {
        public:
            enum class Type {SINGLE,TWO};
            int(*executeFun)(int left, int right);

            std::string getName() const;

            Operator(std::string name, int(*fun)(int left, int right)) {
                this->name = name;
                executeFun = fun;
            }
        private:
            std::string name;
        };

        int handleExpression(std::string expr,const std::vector<Operator>& operators, char variablecall, Register& vars);


        //handler for ( and )

        int handleNormalBexpr(std::string str,const std::vector<Operator>& operators, char variablecall, Register& vars);
        std::tuple<int,std::string> checkNormalBexpr(std::string str, const std::vector<Operator>& operators, char variablecall, Register& vars);

        //handler for variables

        std::string handleVariablesGet(std::string full, InternalLib::Register& reg);
        void handleVariablesSet(std::string full, InternalLib::Register& reg, std::string set);
        std::string checkvariable(char call, std::string check, InternalLib::Register& reg);


        //pre interpreter

        namespace preInterpreter {
            inline std::vector<InternalLib::LangParser::Command> commands;
            
            void preInterpret(InternalLib::Register& GVA, const std::vector<InternalLib::LangParser::Command>& commands, tokenType tokens);
                
        }
    }

    namespace Pincludes {

    }
	
	class c_VOID {
		//void
	public:

		c_VOID() {}

		c_VOID(int) {}
	};
	
	std::string sb(bool bool_);

	bool between(float num, float min, float max);

	size_t searchForVal_i(tokenType str, std::string key);

	std::string searchForVal(tokenType str, std::string key);

    bool allCharactersSame(std::string s, char it);

	namespace random {
		int randomint();

		template<typename T>
		MDEF T randomChoice(T arr[]) {
			return arr[randomint()%(sizeof(arr)/sizeof(T))];
		}

		template<typename T>
		MDEF T randomChoice(std::vector<T> arr) {
			return arr[randomint()%(arr.size()-1)];
		}
	}
}
namespace IL = InternalLib;

#endif