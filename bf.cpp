#include<iostream>
#include<fstream>





char cells[30000];
int currentPointer = 0;


void show_cell();
void StartConsole();
void clear_screen();


void interpret(const std::string& input, int pointer)
{
    if(pointer>=input.length())
    {
        return;
    }
    switch(input[pointer])
    {
    case '+':
        {
            cells[currentPointer]++;
        }
        break;
    case '-':
        {
            cells[currentPointer]--;
        }
        break;
    case '>':
        {
            cells[++currentPointer];
        }
        break;
    case '<':
        {
            if(currentPointer == 0)
            {
                std::cout<<"\n\n]> cannot decrement cell pointer to -1\n\n";
                std::cin.get();

            }
            else
            {
                cells[--currentPointer];
            }
            
        }
        break;
    case '[':
        {
            int nested_loops = 1;

            for(int i = pointer+1;i<input.length();i++)
            {    
                
               { if(input[i] == '[')
                {
                    ++nested_loops;
                }
                else if(input[i] == ']')
                {    
                    --nested_loops; 
                }

               }

                if(nested_loops == 0)
                {

                    std::string exec = input.substr(pointer+1,i-pointer-1);
                    while(cells[currentPointer] != 0)
                    {
                        interpret(exec,0);
                    }
                    pointer = i;

                    break;
                }

                
            }



                
        }
        break;
    case ',':
        {
            
                int in;
                std::cout<<currentPointer<<"]> (input?) ";
                std::cin>>in;
                cells[currentPointer] = (char)in;
        }
        break;
    case '.':
        {
            std::cout<<cells[currentPointer];
        }
        break;
    default:
    {
        //do nothing
    }
        break;

    }

    interpret(input,pointer+1);
}

int main(int argc, char **argv)
{
    std::ifstream inputFile;
    
    std::string arg = argv[1];
    if(argc > 2)
    {
        std::cout<<"too many arguments were given"<<std::endl;
    }
    else if(argc == 2)
    {
        //reading from a file 
        if(arg == "--help" || arg == "-h")
        {
            std::cout<<"\n\nbrainfuck [file/argument] to compile code written in .txt\n";
            std::cout<<"\n\nbrainfuck to start console\n";
            std::cout<<"\n\n--help/-h for help\n\n--console/-console to raise up console\n";
        }
        else if(arg == "--console" || arg == "-c")
        {
            //will bring up interpreter console

            StartConsole();
        }
        else
        {
            

            inputFile = std::ifstream(argv[1]);
            if(!inputFile.is_open())
            {
                std::cout<<"\n\n]> an error occured while trying to find the file or opening it\n\n";
            }
            else
            {
                std::string basic_string,result;

                while(std::getline(inputFile,basic_string))
                {
                    result+=basic_string;
                }

                interpret(result,0);


            }
            
        }
        
    }
    else
    {        
        StartConsole();
    }

    std::cout<<std::endl;
    
    return 0;
}

void StartConsole()
{
    clear_screen();
    std::cout<<"BRAINFUCK\n\n\n\nexit in order to exit/restart to restart\n\n\n";

    while(true)
    {
        std::cout<<currentPointer<<"]> ";
        std::string code;
        std::cin>>code;

        if(code == "exit")
        {
           clear_screen();
           return;
        }

        else if (code == "restart")
        {
            clear_screen();
            for(int i = 0; i <= currentPointer; i++)
            {
                cells[i] = 0;
            }
            currentPointer = 0;
        }

        else if (code == "this")
        {
            show_cell();
        }
        else{

        interpret(code,0);
        }
        
        std::cout<<"\n";
    }

}

void show_cell()
{
    std::cout<<"\n"<<"cell(val/pos): "<<(int)cells[currentPointer]<<"  ["<<currentPointer<<"]"<<"\n\n\n";

}


void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}
