
const int n_MD_types = 11;
std::vector<TString> MD_types = {
    "B1",
    "B2",
    "B3",
    "B4",
    "B5",
    "B6",
    "E1",
    "E2",
    "E3",
    "E4",
    "E5",
};

const int n_LS_types = 14;
std::map<std::pair<int, int>, int> LS_types_map = {
    {{1  , 2}  , 0} , 
    {{2  , 3}  , 1} , 
    {{3  , 4}  , 2} , 
    {{4  , 5}  , 3} , 
    {{5  , 6}  , 4} , 
    {{1  , 7}  , 5} , 
    {{2  , 7}  , 6} , 
    {{3  , 7}  , 7} , 
    {{4  , 7}  , 8} , 
    {{5  , 7}  , 9} , 
    {{7  , 8}  , 10} , 
    {{8  , 9}  , 11} , 
    {{9  , 10} , 12} , 
    {{10 , 11} , 13} , 
};

std::vector<TString> LS_types = {
    "B1B2",
    "B2B3",
    "B3B4",
    "B4B5",
    "B5B6",
    "B1E1",
    "B2E1",
    "B3E1",
    "B4E1",
    "B5E1",
    "E1E2",
    "E2E3",
    "E3E4",
    "E4E5",
};

const int n_pT4_types = 5;
std::map<std::pair<int, int>, int> pT4_types_map = {
    {{1  , 2}  , 0} , 
    {{2  , 3}  , 1} , 
    {{3  , 4}  , 2} , 
    {{4  , 5}  , 3} , 
    {{5  , 6}  , 4} , 
    {{1  , 7}  , 5} , 
    {{2  , 7}  , 6} , 
    {{3  , 7}  , 7} , 
    {{4  , 7}  , 8} , 
    {{5  , 7}  , 9} , 
    {{7  , 8}  , 10} , 
    {{8  , 9}  , 11} , 
    {{9  , 10} , 12} , 
    {{10 , 11} , 13} , 
};

std::vector<TString> pT4_types = {
    "PB1B2",
    "PB2B3",
    "PB3B4",
    "PB4B5",
    "PB5B6",
};

const int n_T4_types = 17;
std::map<std::vector<int>, int> T4_types_map = {
    {{1 , 2 , 3  , 4}  , 0} , 
    {{1 , 2 , 3  , 7}  , 1} , 
    {{1 , 2 , 7  , 8}  , 2} , 
    {{1 , 7 , 8  , 9}  , 3} , 

    {{2 , 3 , 4  , 5}  , 4} , 
    {{2 , 3 , 4  , 7}  , 5} , 
    {{2 , 3 , 7  , 8}  , 6} , 
    {{2 , 7 , 8  , 9}  , 7} , 

    {{3 , 4 , 5  , 6}  , 8} , 
    {{3 , 4 , 5  , 7}  , 9} , 
    {{3 , 4 , 7  , 8}  , 10} , 
    {{3 , 7 , 8  , 9}  , 11} , 

    // {{4 , 5 , 6  , 7}  , 0} ,  // should be impossible
    {{4 , 5 , 7  , 8}  , 12} , 
    {{4 , 7 , 8  , 9}  , 13} , 

    // {{5 , 6 , 7  , 8}  , 0} ,  // should be impossible
    {{5 , 7 , 8  , 9}  , 14} , 

    // {{6 , 7 , 8  , 9}  , 0} ,  // should be impossible

    {{7 , 8 , 9  , 10} , 15} , 
    {{8 , 9 , 10 , 11} , 16} , 
};

std::vector<TString> T4_types = {
    "B1B2B3B4",
    "B1B2B3E1",
    "B1B2E1E2",
    "B1E1E2E3",

    "B2B3B4B5",
    "B2B3B4E1",
    "B2B3E1E2",
    "B2E1E2E3",

    "B3B4B5B6",
    "B3B4B5E1",
    "B3B4E1E2",
    "B3E1E2E3",

    // 4 , 5 , 6  , 7 ,  // should be impossible
    "B4B5E1E2",
    "B4E1E2E3",

    // 5 , 6 , 7  , 8 ,  // should be impossible
    "B5E1E2E3",

    // 6 , 7 , 8  , 9 ,  // should be impossible

    "E1E2E3E4",
    "E2E3E4E5",
};

