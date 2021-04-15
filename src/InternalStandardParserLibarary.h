#ifndef INTERNAL_STANDARD_PARSER_LIBRARY_H_
#define INTERNAL_STANDARD_PARSER_LIBRARY_H_

#include "InternalDef.h"
#include "InternalLib.h"
#include <math.h>

namespace STDParser {
    namespace l = InternalLib;
    
    l::LangParser math = l::LangParser()
                        .addCommand(l::LangParser::Command()
                            .setName("sqrt")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("val")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars[entry["var"]] = std::to_string(std::sqrt(std::stoi(entry["val"])));
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("not")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("val")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars[entry["var"]] = std::to_string(~(std::stoi(entry["val"])));
                            })
                        ->toInstance()
                        )
                    ->toInstance();

    l::LangParser variables = l::LangParser()
                        .addCommand(l::LangParser::Command()
                            .setName("set")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("val")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            auto [ int_, str ] = l::Handlers::checkNormalBexpr(tokens[pos],operators,parser->variablecall,parser->variableRegister);
                                            if( str == "FALSE" ) {
                                                arg.setEntry(std::to_string(int_));
                                            }
                                            else {
                                                arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                            }
                                        })
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars[entry["var"]] = entry["val"];
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("del")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars.erase(entry["var"]);
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("vex")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var2")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars[entry["var2"]] = vars.count(entry["var"]) > 0 ? "1":"0";
                            })
                        ->toInstance()
                        )
                    ->toInstance();
    
    l::LangParser system = l::LangParser()
                        .addCommand(l::LangParser::Command()
                            .setName("ext")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("c")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->setType(l::LangParser::Command::Arg::ASET)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                if(entry["c"] != "") {
                                    std::cout << "Programm " << vars["__file__"] << " exited with code: " << entry["c"] << "\n";
                                }
                                parser->off();
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("exe")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("coms")
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            DEBUG_MESSAGE("first: \"" <<tokens[pos][0] << "\" second: \"" << tokens[pos][tokens[pos].size()-1] << "\"" )
                                            if(tokens[pos][0] == '{' && tokens[pos][tokens[pos].size()-1] == '}') {
                                                arg.setEntry(tokens[pos]);
                                            }
                                            else {
                                                throw SyntaxError{};
                                            }
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("sv") //save-variables
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("no") //not-open
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                if(entry["sv"] == "1") {
                                    parser->parse(entry["coms"].substr(1,entry["coms"].size()-2));
                                }
                                else {
                                    parser->toInstance().parse(entry["coms"].substr(1,entry["coms"].size()-2));
                                }
                                if(entry["no"] == "") {
                                    parser->unlock();
                                }
                                
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("con")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("cond") //condition
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            auto [ int_, str ] = l::Handlers::checkNormalBexpr(tokens[pos],operators,parser->variablecall,parser->variableRegister);
                                            if( str == "FALSE" ) {
                                                arg.setEntry(std::to_string(int_));
                                            }
                                            else {
                                                arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                            }
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("coms") //commands
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            DEBUG_MESSAGE("checking: \"" << tokens[pos][0] << "\" != { || \"" << tokens[pos][tokens[pos].size()-1] << "\" != }")
                                            if(tokens[pos][0] != '{' || tokens[pos][tokens[pos].size()-1] != '}') {
                                                throw ParametherMissmatchError{};
                                            }
                                            arg.setEntry(tokens[pos].substr(1,tokens[pos].size()-2));

                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("e") //else
                                        ->setType(l::LangParser::Command::Arg::ASET)
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            DEBUG_MESSAGE("checking: \"" << tokens[pos][0] << "\" != { || \"" << tokens[pos][tokens[pos].size()-1] << "\" != }")
                                            if(tokens[pos][0] != '{' || tokens[pos][tokens[pos].size()-1] != '}') {
                                                throw ParametherMissmatchError{};
                                            }
                                            arg.setEntry(tokens[pos].substr(1,tokens[pos].size()-2));
                                        })
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("n") //not
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("sv") //save-variables
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                bool cond = entry["cond"] == "1";
                                if(entry["n"] == "1") {
                                    cond = !cond;
                                }
                                if(cond) {
                                    if(entry["sv"] == "1") {
                                        parser->parse(entry["coms"]);
                                    }
                                    else {
                                        parser->toInstance().parse(entry["coms"]);
                                    }
                                }
                                else if(entry["e"] != "") {
                                    if(entry["sv"] == "1") {
                                        parser->parse(entry["e"]);
                                    }
                                    else {
                                        parser->toInstance().parse(entry["e"]);
                                    }
                                }
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("slp")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("secs")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                mac::tsleep(std::stoi(entry["secs"])*1000);
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("stp")
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                mac::pause();
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("run")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("cond")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            if(tokens[pos][0] != '(' || tokens[pos][tokens[pos].size()-1] != ')') {
                                                throw ParametherMissmatchError{};
                                            }
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("coms")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            if(tokens[pos][0] != '{' || tokens[pos][tokens[pos].size()-1] != '}') {
                                                throw ParametherMissmatchError{};
                                            }
                                            arg.setEntry(tokens[pos].substr(1,tokens[pos].size()-2));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("e") //equalation
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                if(entry["e"] == "1") {
                                    std::cout << "x" << "\n";
                                    bool check = check = l::Handlers::handleNormalBexpr(entry["cond"],parser->operators,parser->variablecall,parser->variableRegister) == 1;
                                    std::cout << "x" << "\n";
                                    while(check) {
                                        std::cout << "x" << "\n";
                                        parser->toInstance().parse(entry["coms"]);

                                        check = l::Handlers::handleNormalBexpr(entry["cond"],parser->operators,parser->variablecall,parser->variableRegister) == 1;
                                    }
                                }
                                else {
                                    for(size_t i = 0; i < l::Handlers::handleNormalBexpr(entry["cond"],parser->operators,parser->variablecall,parser->variableRegister); ++i) {
                                        vars["__loop_val__"] = std::to_string(i);
                                        parser->toInstance().parse(entry["coms"]);
                                    }
                                    vars.erase("__loop_val__");
                                }
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("jmp")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("pos")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(InternalLib::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("d")
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                size_t jmpPos = std::stoi(entry["pos"]);
                                if(entry["d"] == "1") {
                                    jmpPos = std::stoi(vars["__line__"]) + std::stoi(entry["pos"]);
                                }
                                *parser->pos = parser->lineRegister[jmpPos];
                            })
                        ->toInstance()
                        )
                    ->toInstance();

    l::LangParser io = l::LangParser()
                        .addCommand(l::LangParser::Command()
                            .setName("out")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("text")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                       })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("nnl")
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                if(entry["nnl"] == "") {
                                    std::cout << entry["text"] << std::endl;
                                }
                                else {
                                    std::cout << entry["text"];
                                }
                            })
                        ->toInstance()
                        )
                        ->addCommand(l::LangParser::Command()
                            .setName("red")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("var")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("t")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->setType(l::LangParser::Command::Arg::ASET)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                std::cout << entry["t"];
                                std::getline(std::cin,vars[entry["var"]]);
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("fout")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("file")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("buffer")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(tokens[pos]);
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                vars[entry["buffer"]] = InternalFsys::readNormal(entry["file"]);
                            })
                        ->toInstance()
                        )
                    ->addCommand(l::LangParser::Command()
                            .setName("fin")
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("file")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("text")
                                        ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                            arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                        })
                                        ->setType(l::LangParser::Command::Arg::AGET)
                                        ->toInstance()
                                    )
                            ->addArg(l::LangParser::Command::Arg()
                                        .setName("t") //trunc
                                        ->setType(l::LangParser::Command::Arg::ATAG)
                                        ->toInstance()
                                    )
                            ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                InternalFsys::writeNormal(entry["file"],entry["text"],entry["t"] == "1");
                            })
                        ->toInstance()
                        )
                ->toInstance();
    
    inline l::LangParser external = l::LangParser()
                                        .addCommand(l::LangParser::Command()
                                                .setName("inc")
                                                ->addArg(l::LangParser::Command::Arg()
                                                    .setName("file")
                                                    ->setType(l::LangParser::Command::Arg::AGET)
                                                    ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                                        arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                                    })
                                                    ->toInstance()
                                                )
                                                ->addArg(l::LangParser::Command::Arg()
                                                    .setName("lib")
                                                    ->setType(l::LangParser::Command::Arg::ATAG)
                                                    ->toInstance()
                                                )
                                                ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                                    if(entry["lib"] == "1") {
                                                        parser->parse(InternalFsys::readNormal(parser->pathToStdlib.string() + ST + entry["file"]),false);
                                                    }
                                                    else {
                                                        parser->parse(InternalFsys::readNormal(entry["file"]),false);
                                                    }
                                                })
                                                ->toInstance()
                                            )
                                    ->addCommand(l::LangParser::Command()
                                                .setName("lik")
                                                ->addArg(l::LangParser::Command::Arg()
                                                    .setName("path")
                                                    ->setType(l::LangParser::Command::Arg::AGET)
                                                    ->sgetFun([](l::LangParser::Command::Arg& arg,tokenType& tokens,l::Register& vars,size_t& pos, const std::vector<InternalLib::Handlers::Operator>& operators, l::LangParser* parser) {
                                                        arg.setEntry(l::Handlers::checkvariable(parser->variablecall,tokens[pos],vars));
                                                    })
                                                    ->toInstance()
                                                )
                                                ->setExecute([](l::LangParser::Command*,l::Register& vars,l::Register& entry,l::LangParser* parser) {
                                                    parser->pathToStdlib = entry["path"];
                                                })
                                                ->toInstance()
                                            )
                                        ->toInstance();
}

namespace STDOperators {
    namespace l = InternalLib;
    l::Handlers::Operator plus("+",[](int left, int right)->int {
        return left + right;
    });
    l::Handlers::Operator minus("-",[](int left, int right)->int {
        return left - right;
    });
    l::Handlers::Operator times("*",[](int left, int right)->int {
        return left * right;
    });
    l::Handlers::Operator div("/",[](int left, int right)->int {
        return left / right;
    });
    l::Handlers::Operator power("^",[](int left, int right)->int {
        return std::pow(left,right);
    });
    l::Handlers::Operator band("&",[](int left, int right)->int {
        return left & right;
    });
    l::Handlers::Operator bor("|",[](int left, int right)->int {
        return left | right;
    });
    l::Handlers::Operator mod("%",[](int left, int right)->int {
        return left % right;
    });
    l::Handlers::Operator bxor("#",[](int left, int right)->int {
        return left ^ right;
    });
    l::Handlers::Operator equal("==",[](int left, int right)->int {
        return left == right;
    });
    l::Handlers::Operator nequal("!=",[](int left, int right)->int {
        return left != right;
    });
    l::Handlers::Operator land("&&",[](int left, int right)->int {
        return (left==1 && right==1) ? 1:0;
    });
    l::Handlers::Operator lor("||",[](int left, int right)->int {
        return (left==1 || right==1) ? 1:0;
    });
}

#endif