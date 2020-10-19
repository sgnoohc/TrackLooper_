
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

