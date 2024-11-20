static string itos(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

static string ftos(float number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

static bool alphaNumericallyLessThan(const string& s1, const string& s2)
{ 
    //AlphaNumeric test...
    unsigned int tSize = s1.size() < s2.size() ? s1.size() : s2.size();

    for(int i=0; i<tSize; i++)
    {
        //English ASCII sort helper to make the sort case insensitive. Other languages using UTF8 will be SOL.
        unsigned int c1 = (s1[i] >= 97 && s1[i] <= 122) ? s1[i] - 32 : s1[i];
        unsigned int c2 = (s2[i] >= 97 && s2[i] <= 122) ? s2[i] - 32 : s2[i];

        if(c2 > c1){ return true; }
        if(c2 < c1){ return false; }
    }

    //Default return
    return true;
}

static void sortAlphaNumerically(vector<string>& strings)
{
    //Return if empty
    if(strings.size() == 0){ return; }

    //Sort
    vector<string>sortedStrings;
    sortedStrings.push_back(strings[0]);

    for(int i=1; i<strings.size(); i++)
    {
        bool append = true;
        for(int j=0; j<sortedStrings.size(); j++)
        {
            if(!alphaNumericallyLessThan(sortedStrings[j], strings[i]))
            {
                sortedStrings.insert(sortedStrings.begin() + j, strings[i]);
                append = false;
                break;
            }
        }

        if(append)
        {
            sortedStrings.push_back(strings[i]);
        }
    }

    //Assign from sorted
    strings = sortedStrings;
}

static void splitByWhiteSpace(const string& str, vector<string>& splitStr)
{
    //Clear incomming
    splitStr.clear();

    //Split
    const char *start = str.c_str();
    const char *end   = start + str.size();
    const char *token = start;

    while(start!=end)
    {
        if(isspace(*start))
        {
            if(token < start)
            { 
                splitStr.push_back(string(token, start));
                if(splitStr.back() == " "){ splitStr.pop_back(); } //Dont allow empty
            }

            start++;
            token = start;
        }

        else{ start++; }
    } 

    if(token < start)
    { 
        splitStr.push_back(string(token, start));
        if(splitStr.back() == " "){ splitStr.pop_back(); } //Dont allow empty
    }
}
