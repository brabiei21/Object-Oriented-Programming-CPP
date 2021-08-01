#include "MadlibAutoWordProvider.hpp"

MadlibAutoWordProvider::MadlibAutoWordProvider(const MadlibAutoWordProvider &aAutoProvider){}
MadlibAutoWordProvider &MadlibAutoWordProvider::operator=(const MadlibAutoWordProvider &aAutoProvider){return *this;}
MadlibAutoWordProvider::~MadlibAutoWordProvider(){}

MadlibAutoWordProvider::MadlibAutoWordProvider() : MadlibWordProvider()
{
    //provide a json file that's loaded with starter words
    readJSON("words.json");
}

//ask chatbot for word of given type; return that to caller...
std::string MadlibAutoWordProvider::getSubstituteWord(WordType aType)
{
    std::string word = "empty";


    seed = rand();
    srand(seed);

    //get bot to give you random word of given type...
    //Don't forget to handle the special case of plural nouns
    std::string type;
    int number = int(aType);
    int position;

    switch(number)
    {
        case 0:
        {
            type = "invalid";
            return type;
            break;
        }
        case 1:
        {
            type = "noun";
            position = rand() % word_list.size();
            while (word_list[position].pos != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        case 2:
        {

            //plural noun
            type = "noun";
            position = rand() % word_list.size();
            while (word_list[position].pos != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;
            word = word + "s";

            break;
        }
        case 3:
        {
            type = "name";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        case 4:
        {
            type = "verb";
            position = rand() % word_list.size();
            while (word_list[position].pos != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;

        }
        case 5:
        {
            type = "adjective";
            position = rand() % word_list.size();
            while (word_list[position].pos != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;

        }
        case 6:
        {
            type = "adverb";
            position = rand() % word_list.size();
            while (word_list[position].pos != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;

        }
        case 7:
        {
            type = "number";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        case 8:
        {
            type = "color";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        case 9:
        {
            type = "fruit";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;


            break;
        }
        case 10:
        {
            type = "animal";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        case 11:
        {
            type = "place";
            position = rand() % word_list.size();
            while (word_list[position].category != type)
            {
                position = rand() % word_list.size();
            }
            word = word_list[position].word;

            break;
        }
        default:
            type = "Not sure what you gave me.";
            return type;
    }
    return word;
}

bool MadlibAutoWordProvider::readJSON(const char *jsonPath)
{
   std::ifstream f;
   f.open(jsonPath);
   if(!f.is_open()) {
      std::cerr << "Error opening JSON file!" << std::endl;
      return false;
   }
   std::string line, word, first_split;
   while (!f.eof()) {
      WORD curr_line;
      if (line.find("\"WORD\"") != std::string::npos) {
         first_split = line.substr(line.find(":"), line.find("\","));
         word = first_split.substr(first_split.find("\"")+1, first_split.find("\",")-3);
         curr_line.word = word;
         std::getline(f, line);
      }
      if(line.find("\"POS\"") != std::string::npos){
         first_split = line.substr(line.find(":"), line.find(","));
         word = first_split.substr(first_split.find("\"")+1, first_split.find("\",")-3);
         curr_line.pos = word;
         std::getline(f, line);
      }
      if(line.find("\"CATEGORY\"") != std::string::npos){
         first_split = line.substr(line.find(":"), line.find(","));
         if(first_split.compare(": \"\"") != 0) {
            word = first_split.substr(first_split.find("\"")+1, first_split.find_last_of("\"")-3);
            curr_line.category = word;
         }
         word_list.push_back(curr_line);
         std::getline(f, line);
      }
      else
      {
         std::getline(f, line);
      }
   }
   return true;
}

