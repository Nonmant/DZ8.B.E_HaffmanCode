#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"2\n"
                  "DUDDUU\n"
                  "DU";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "4\n"
                            "0\n"
                            "100\n"
                            "101\n"
                            "11\n"
                            "2\n"
                            "0\n"
                            "1\n");
}

TEST_CASE("One left leaf", ""){
    std::stringstream input(
                            "1\n"
                            "D\n");
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
    "1\n"
    "0\n"
    );
}
