
#include "UtilClient.h"


std::string UtilClient::buildContext(std::string path, const char* delims)
{

    char* charPath = &path[0];
    char* token = NULL;
    std::string context;

    // Establish string and get the first token:
    token = strtok(charPath, delims);

    // While there are tokens in charPath
    while ((token != NULL))
    {
        // Get next token:
        if (token != NULL)
        {
            context += token;
            context += SEPARATOR;
            token = strtok(NULL, delims);
        }
    }

    return context;
}
void UtilClient::infoText()
{
    std::cout << std::endl << std::endl;
    std::string text = "";
    text.append("Observatory\n");
    text.append("\t[space]\t-> on/of laser\n");
    text.append("\t[wasd] \t-> move spot light\n");
    text.append("\t[rt]   \t-> rotate sx,dx observatory\n");
    text.append("\t[h]    \t-> open, close dome\n");
    text.append("Camera\n");
    text.append("\t[jl]   \t-> rotate camera sx,dx\n");
    text.append("\t[ik]   \t-> rotate camera up, down\n");
    text.append("\t[uo]   \t-> zoom-in, zoom-out camera\n");
    text.append("\t[x]    \t-> reset camera\n");
    text.append("Select Camera\n");
    text.append("\t[1]    \t-> front view\n");
    text.append("\t[2]    \t-> above viev\n");
    text.append("\t[3]    \t-> 'human' view\n");
    text.append("\t[4]    \t-> rear view\n");
    text.append("Text\n");
    text.append("\t[v]    \t-> show/hide FPS\n");

    std::cout << text << std::endl;
}




