#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<stack>
#include<deque>
#include <limits.h>

int main(int argc, char* argv[])
{	
	//CHECK FOR NUMBER OF COMMAND LINE ARGS
	if(argc < 2)
	{
		std::cout << "Too few command-line arguments.\n";
		return 1;
	}
	else if(argc > 2)
	{
		std::cout << "Too many command-line arguments.\n";
		return 1;
	}
	
	std::stack<std::string> undo;							//undo stack
	std::stack<std::string> redo;							//redo stack

	std::deque<std::string> beforeSave;

	std::string line;							//input from file
	std::string input = "";						//take input for command

	std::stringstream inputStream(input);
	std::stringstream undoRedoStream("");

	std::string token;							//token for splitting command input
	std::string currentStr;
	std::vector<std::string> command;			//store tokenized strings	
	command.push_back("");						//	Initialize the max two components of the command
	command.push_back("");						//

	unsigned count = 0;							//line count variable 
	unsigned start = 2;							//keep track of which col to start the window starts on
	unsigned cursorVertical = 0;
	unsigned cursorHorizontal = 0;
	unsigned max = 12;
	unsigned cmdLength = 0;
	unsigned undoRedoHorizontal = 0;
	unsigned undoRedoVertical = 0;
	unsigned undoRedoLen = 0;
	std::string undoRedoStr = "";
	unsigned undoRedoCount = 0;
	unsigned insertNum = 0;
	unsigned beforeSaveLength = 0;
	unsigned temp = 0;
	unsigned difTemp;

	unsigned int where;

	int num = 0;
	unsigned undoCount = 0;
	unsigned redoCount = 0;

	unsigned lenMultLines;
	unsigned lineMultLines;
	unsigned nextStartMultLines;
	std::string strToPrint;
	std::string strToPush;

	bool firstIteration = true;
	//OPEN INPUT FILE
	std::ifstream inputFile;
	inputFile.open( argv[1], std::ifstream::in);

	if(!inputFile)
	{
		std::cout << "Failed to open file: " << argv[1] << "\n";
		return 2;
	}

	std::vector<std::string> window;
	window.push_back("     *");
	window.push_back("     12345678901234567890");

	for(int i = 1; i <= 40; ++i)
	{
		if(i >= 10)
			window.push_back("  " + std::to_string(i));
		else
			window.push_back("   " + std::to_string(i));
	}

	window[2].replace(0, 1, "*");

	//READ LINES FROM INPUT FILE
	while( getline(inputFile, line) )
	{
		if(count == 30)
		{
			std::cout << "File " << argv[1] << " has too many lines.\n";
			return 2;
		}
		else if(line.length() > 20)	
		{
			std::cout << "File"  << argv[1] << " has at least one too long line.\n";
			return 2;
		}

		window[count+2].append("|" + line);
		count++;
	}

	//MAIN LOOP
	while(true)
	{
		//OUPUT THE WINDOW
		std::cout << window[0] << std::endl;
		std::cout << window[1] << "\n";

		for (unsigned i = start; i < start+10; ++i)
			std::cout << window[i] << "\n";

		std::cout << window[1] << "\n";

		//READ COMMANDS
		input = "";
		std::cout << "Enter command: ";
		std::getline(std::cin, input);
		inputStream.str( std::string() );
		inputStream.clear();
		inputStream << input;

		std::cout << std::endl;

		if(!input.empty())
		{
			command[0] = "";
			command[1] = "";
	
			std::getline(inputStream, token, ' ');
			command[0] = token;	
			cmdLength = token.length();

			if(std::getline(inputStream, token, ' ') )
				command[1] = input.substr(cmdLength + 1, std::string::npos);
		}

		if(command[0] == "q")		//QUIT COMMAND
		{
			if(insertNum != 0 || beforeSave.size() != beforeSaveLength)		//CHECK IF THERE ARE UNSAVED CHANGES
			{
				std::cout << "You have unsaved changes.\nAre you sure you want to quit (y or n)?\n";
				std::getline(std::cin, input);

				if(input == "n")	//DON'T WANT TO QUIT, CONTINUE LOOP
					continue;
			}
			std::cout << "Goodbye!\n";
			return 0;

		}else if(command[0] == "save")			//SAVE COMMAND
		{
			//SAVE THE FILE
			std::ofstream fileToSave;			//OVERWRITE FILE TO SAVE
			fileToSave.open(command[1]);

			for(unsigned i = 2; i < 2 + count; i++)
				fileToSave << window[i].substr(5, 20) << std::endl;

			insertNum = 0;

			while(!undo.empty())
			{
				beforeSave.push_front(undo.top());
				undo.pop();
			}

			beforeSaveLength = beforeSave.size();

		}else if(command[0] == "a")				//MOVE CURSOR LEFT
		{
			//move cursor left
			if(!command[1].empty())
			{
				if((int)cursorHorizontal - std::stoi(command[1]) >= 0)	//(S, NUM TO MOVE COMMAND)CHECK THAT CURSOR STAYS IN BOUND
				{
					cursorHorizontal -= std::stoi(command[1]);
					goto updateHorizontalCursor;
				}else													//IF CURSOR - NUM TO MOVE < 0, GO AS FAR LEFT AS POSSIBLE
				{
					cursorHorizontal = 0;
					goto updateHorizontalCursor;
				}
			}else if(cursorHorizontal != 0)								//(S COMMAND) IF CURSOR IS NOT ON FAR LEFT, MOVE LEFT BY 1
			{
				cursorHorizontal -= 1;
				goto updateHorizontalCursor;
			}

		}else if(command[0] == "d")
		{
			//move cursor right
			if(!command[1].empty())
			{
				if(std::stoi(command[1]) + cursorHorizontal <= 20)		
				{
					cursorHorizontal += std::stoi(command[1]);
					goto updateHorizontalCursor;
				}else
				{
					cursorHorizontal = 19;
					goto updateHorizontalCursor;
				}
			}else if(cursorHorizontal != 19)
			{
				cursorHorizontal += 1;
				goto updateHorizontalCursor;
			}

		}else if(command[0] == "w")
		{
			//move cursor up
			if(!command[1].empty())
			{
				if((int)cursorVertical - std::stoi(command[1]) >= 0)
				{
					window[cursorVertical + 2].replace(0, 1, " ");
					cursorVertical -= std::stoi(command[1]);

					if(cursorVertical + 2 < start)
					{
						start = cursorVertical + 2;
						max = start + 10;
					}

					goto updateVerticalCursor;
				}else
				{
					window[cursorVertical+2].replace(0, 1, " ");
					start = 2;
					max = start + 10;
					cursorVertical = 0;
					window[cursorVertical+2].replace(0, 1, "*");

				}
			}else if((int)cursorVertical - 1 >= 0)
			{
				window[cursorVertical + 2].replace(0, 1, " ");
				cursorVertical -= 1;

				if(cursorVertical + 2 < start)
				{
					start = cursorVertical + 2;
					max = start + 10;
				}

				goto updateVerticalCursor;
			}
		}else if(command[0] == "s")
		{
			//move cursor down
			if(!command[1].empty())
			{
				if(cursorVertical + std::stoi(command[1]) <= 29)
				{
					if( (int)cursorVertical + std::stoi(command[1]) + 1 > (int)count)
					{
						window[cursorVertical + 2].replace(0, 1, " ");

						if( (unsigned)std::stoi(command[1]) <= (count - 1 - cursorVertical) + (count - (start-1)) )
							start += std::stoi(command[1]) - ( count - (cursorVertical + 1));
						else
							start = count + 1;

						max = start+10;

						cursorVertical = count - 1;

						window[cursorVertical+2].replace(0, 1, "*");
						continue;
					}
		
					if( (int)count - 1 == (int)cursorVertical)	
					{
						start += std::stoi(command[1]);
						max = start + 10;
						continue;
					}

					if(start + std::stoi(command[1]) >= max)
					{
						start += std::stoi(command[1]) - max + 3; 
						max = start+10;
					}
					

					window[cursorVertical + 2].replace(0, 1, " ");
					cursorVertical += std::stoi(command[1]);
		
					goto updateVerticalCursor;
				}else
				{
					window[cursorVertical + 2].replace(0, 1, " ");
					start = count + 1;
					max = start+10;
					cursorVertical = count - 1;
					window[cursorVertical+2].replace(0, 1, "*");
				}
			}else if(cursorVertical + 1 <= 29)
			{
				if( (int)count - 1 == (int)cursorVertical)
				{
					if(	start - 1 == count )
						continue;

					start += 1;
					max = start + 10;
					continue;
				}

				window[cursorVertical + 2].replace(0, 1, " ");
				cursorVertical += 1;

				if(cursorVertical + 2 >= max)
				{
					max = cursorVertical + 2;
					start = max - 9;
				}

				goto updateVerticalCursor;
			}else
			{
				if(start < 31)
					start+=1;

				max = start + 10;
				goto updateVerticalCursor;
			}
		}else if(command[0] == "i")
		{
			insertNum++;

			while(!redo.empty())
				redo.pop();
			
			if(cursorHorizontal + command[1].length() <= 20)
			{
				if(window[cursorVertical+2].length() <= 5)
				{
					//std::cout <<"hi\n";
					//std::cout << std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(command[1].length()) << std::endl;
					undo.push(std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(command[1].length()));
				}else
				{
					if(5+cursorHorizontal >= window[cursorVertical+2].length())
					{
						//std::cout <<"WE \n";
						//std::cout <<  std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(command[1].length()) + "-" + std::string(undoRedoStr.length(), ' ') << std::endl;
						undo.push(std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(window[cursorVertical+2].length()) + "-" + std::string(undoRedoStr.length(), ' '));				
					}else
					{
						//std::cout <<"WE HERE\n";
						//std::cout << std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(window[cursorVertical+2].length()) + "-" + window[cursorVertical+2].substr(5, std::string::npos) << std::endl;
						undo.push(std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(window[cursorVertical+2].length()) + "-" + window[cursorVertical+2].substr(5, std::string::npos));
					}
				}	
				
				if(cursorHorizontal + 5 > window[cursorVertical + 2].length())
				{
					window[cursorVertical+2] = window[cursorVertical+2] + std::string(cursorHorizontal+5-window[cursorVertical+2].length(), ' ') + command[1];

				}else
					window[cursorVertical+2].replace(cursorHorizontal + 5, command[1].length(), command[1]);

				if(cursorVertical >= count)
				{
					for(unsigned i = count; i <= cursorVertical; i++)
						window[i+2].replace(4,1,"|");

					count = cursorVertical + 1;
				}
			}
			else
			{
				std::cout << "1\n";
				num = cursorHorizontal + command[1].length();
				undoCount = 0;

				while(num > 0)
				{
					num -= 20;
					undoCount++;
				}

				lenMultLines = 20 - cursorHorizontal;
				lineMultLines = 2;
				nextStartMultLines = lenMultLines;
				strToPrint = command[1].substr(0, lenMultLines);
				firstIteration = true;

				while(true)
				{
					if(lineMultLines - 2 == 0 && cursorHorizontal + 5 >= window[cursorVertical + 2].length())
					{
						std::cout << "2\n";
						//std::cout << std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(strToPrint.length()) << std::endl;
						undo.push(std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical) + "-" + std::to_string(strToPrint.length()));
						window[cursorVertical+2] = window[cursorVertical+2] + std::string(cursorHorizontal+5-window[cursorVertical+2].length(), ' ') + strToPrint;
					}else 
					{
						if(cursorVertical + lineMultLines - 1 > 30)
							break;

						if(cursorVertical + lineMultLines - 1 > count)
						{
							std::cout << "3\n";
							window[cursorVertical+lineMultLines] = window[cursorVertical + lineMultLines] + "|" + strToPrint;
							count++;
						}else
						{
							if(firstIteration)
							{
								std::cout << "4\n";
								//std::cout << std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical+lineMultLines-2) + "-" + std::to_string(strToPrint.length()) + "-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos) << std::endl;
								undo.push(std::to_string(cursorHorizontal) + "-" + std::to_string(cursorVertical+lineMultLines-2) + "-" + std::to_string(strToPrint.length()) + "-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos));
								firstIteration = false;
							}

							window[cursorVertical + lineMultLines].replace(5, strToPrint.length(), strToPrint);
						}


					}

					strToPrint = command[1].substr(nextStartMultLines, std::string::npos);
					lineMultLines++;

					if(strToPrint.length() > 20)
					{
						std::cout << "5\n";
						//std::cout << "0-"+ std::to_string(cursorVertical+lineMultLines-2)+"-20-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos) << std::endl;
						if(window[cursorVertical+lineMultLines].length() < 5)
							undo.push("0-"+ std::to_string(cursorVertical+lineMultLines-2)+"-20- ");
						else
							undo.push("0-"+ std::to_string(cursorVertical+lineMultLines-2)+"-20-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos));
						
						strToPrint = command[1].substr(nextStartMultLines, 20);
						nextStartMultLines += 20;
					}else
					{	
						std::cout << "6\n";
						//std::cout << "0-" + std::to_string(cursorVertical+lineMultLines-2) +"-" + std::to_string(strToPrint.length()) + "-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos) + "-" + std::to_string(undoCount) << std::endl;
						
						if(window[cursorVertical+lineMultLines].length() < 5)
							undo.push("0-" + std::to_string(cursorVertical+lineMultLines-2) + "-" + std::to_string(strToPrint.length()) + "- -" + std::to_string(undoCount));
						else
							undo.push("0-" + std::to_string(cursorVertical+lineMultLines-2) + "-" + std::to_string(strToPrint.length()) + "-" + window[cursorVertical+lineMultLines].substr(5, std::string::npos) + "-" + std::to_string(undoCount));

						if(cursorVertical + lineMultLines - 1 > count)
						{
							std::cout << "7\n";
							window[cursorVertical+lineMultLines] = window[cursorVertical+lineMultLines] + "|" + strToPrint;
							count++;
						}else
						{
							std::cout << "8\n";
							if(window[cursorVertical + lineMultLines].length() <= 5)
								window[cursorVertical + lineMultLines] = window[cursorVertical + lineMultLines] + strToPrint;
							else
								window[cursorVertical + lineMultLines].replace(5, strToPrint.length(), strToPrint);	
						}	
						strToPush += strToPrint;
						break;
					}
				}
			}

		}else if(command[0] == "u")
		{		

			if(insertNum == 0 && beforeSave.empty())
			{
				std::cout << "Cannot undo.\n\n";
				continue;
			}
			temp = insertNum;

			if(insertNum != 0)
				insertNum--;
			
			undoCount = 1;
			firstIteration = true;
			difTemp = 1;

		undo:
			undoRedoStream.str( std::string() );
			undoRedoStream.clear();

			if(temp == 0)
			{
				undoRedoStream << beforeSave.back();
				beforeSave.pop_back();
				where = 1;
			}else
			{	
				undoRedoStream << undo.top();
				undo.pop();
				where = 2;
			}

			undoRedoHorizontal = 0;
			undoRedoVertical = 0;
			undoRedoLen = 0;
			undoRedoStr = "";
			undoRedoCount = 0;

			while(std::getline(undoRedoStream, token, '-'))
			{
				if(undoRedoCount == 0)
					undoRedoHorizontal = std::stoi(token);
				else if(undoRedoCount == 1)
					undoRedoVertical = std::stoi(token);
				else if(undoRedoCount == 2)
					undoRedoLen = std::stoi(token);
				else if(undoRedoCount == 3)
					undoRedoStr = token;
				else if(undoRedoCount == 4)
				{
					if(firstIteration)
					{
						undoCount = std::stoi(token);
						difTemp = undoCount;
						firstIteration = false;
					}
				}
				undoRedoCount++;
			}

			if(insertNum == 0)
			{
				if(difTemp == 1 && undoCount > 1)
				{
					//std::cout <<std::to_string(where) + "-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) +"-"+std::to_string(undoCount) << std::endl;
					redo.push(std::to_string(where) + "-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) + "-" + std::to_string(undoCount));
				}else
				{
					//std::cout << "0-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) << std::endl;
					redo.push("0-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen));
				}
			}else
			{
				if(difTemp == 1 && undoCount > 1)
				{
					//std::cout << std::to_string(where) + "-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) + "-"+ std::to_string(undoCount) << std::endl;
					redo.push(std::to_string(where) + "-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) + "-" + std::to_string(undoCount));
				}
				else
				{
					//std::cout << "0-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) << std::endl;
					redo.push("0-" + std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen));
				}
			}

			if(undoRedoStr.empty())
			{
				window[undoRedoVertical + 2].erase( 5 + undoRedoHorizontal, undoRedoLen);
				continue;
			}
	
			window[undoRedoVertical + 2].replace( 5 + undoRedoHorizontal, std::string::npos, undoRedoStr );
			difTemp--;

			if(difTemp > 0)
				goto undo;

 		}else if(command[0] == "r")
		{
			if(redo.empty())
			{
				std::cout << "Cannot redo.\n\n";
				continue;
			}

			firstIteration = true;
			redoCount = 1;
			temp = 1;

		redo:
			undoRedoStream.clear();
			undoRedoStream << redo.top();
			undoRedoCount = 0;
			while(std::getline(undoRedoStream, token, '-'))
			{
				if(undoRedoCount == 0)
					where = std::stoi(token);
				else if(undoRedoCount == 1)
					undoRedoHorizontal = std::stoi(token);
				else if(undoRedoCount == 2)
					undoRedoVertical = std::stoi(token);
				else if(undoRedoCount == 3)
					undoRedoLen = std::stoi(token);
				else if(undoRedoCount == 4)
					undoRedoStr = token;
				else
				{
					if(firstIteration)
					{
						redoCount = std::stoi(token);
						temp = redoCount;
						firstIteration = false;
					}
				}
				undoRedoCount++;
			}

			if(undoRedoStr.empty())
			{
				window[undoRedoVertical + 2].erase( 5 + undoRedoHorizontal, undoRedoLen);
				continue;
			}

			if(where == 2)
				insertNum += 1;

			if(insertNum == 0)
			{
				if(temp == 1 && redoCount > 1)
				{
					//std::cout << "cuh" <<std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos) + "-" + std::to_string(redoCount)<< std::endl;
					beforeSave.push_back( std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos) + "-" + std::to_string(redoCount));
				}else
				{
					//std::cout << "mane" << std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) << std::endl;
					beforeSave.push_back( std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical) + "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, undoRedoLen) );
				}
			}else
			{
				if(temp == 1 && redoCount > 1)
				{
					//std::cout << "heeem" <<std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical)+ "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos) + "-" + std::to_string(redoCount) << std::endl;
					undo.push( std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical)+ "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos) + "-" + std::to_string(redoCount));
				}else
				{
					//std::cout <<"yeeeee" << std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical)+ "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos) << std::endl;
					undo.push( std::to_string(undoRedoHorizontal) + "-" + std::to_string(undoRedoVertical)+ "-" + std::to_string(undoRedoLen) + "-" + window[undoRedoVertical+2].substr(5+undoRedoHorizontal, std::string::npos));
				}
			}

			window[undoRedoVertical + 2].replace( 5 + undoRedoHorizontal, undoRedoLen, undoRedoStr );
			temp--;
			redo.pop();
			std::cout << temp << "\n";

			if(temp > 0)
				goto redo;
		}

		continue;

	updateHorizontalCursor: 
		window[0] = "";

		for(unsigned i = 0; i < 5 + cursorHorizontal; i++)
			window[0].append(" ");

		window[0].append("*");
		continue;

	updateVerticalCursor:
		window[cursorVertical + 2].replace(0, 1, "*");
	}
}


























