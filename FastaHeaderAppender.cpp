// FastaHeaderAppender just adds some characters to the end of
// each header in a fasta file.
// It optionally replaces each space with an underscore.
// It assumes that a header occurs every other line of the file.
// Contact Adam Jones, ajones@bio.tamu.edu, with questions.

// Usage:
// -i:	Fasta Input Filename
// -o:	Output Filename
// -s:  String to add
// -u:  Replace spaces with underscores (y or n) 
// -h: Help
// no arguments: Interactive

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class fasta_record {
public:
	string header;
	string sequence;
};

int main( int argc, char* argv[] )
{
	int i;
	string infile_name_string, outfile_name_string;
	string append_string;
	char* infile_name;
	char* outfile_name;
	bool interactivemode = false;
	int replace_spaces;

	string query;
	string tempstring1, tempstring2;

	if (argc == 1)
	{
		cout << "\n(I)nteractive or (H)elp?\n";
		cin >> query;
		if (query == "H" || query == "h")
		{
			cout << "\nFastaHeaderAppender\n";
			cout << "-i:\tinput file\n";
			cout << "-o:\toutput file\n";
			cout << "-s:\tstring to append\n";
			cout << "-u:\treplace spaces with underscores (y or n)\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	if (argc > 1)
	{
		tempstring1 = argv[1];
		if (tempstring1 == "-h")
		{
			cout << "\nFastaHeaderAppender\n";
			cout << "-i:\tinput file\n";
			cout << "-o:\toutput file\n";
			cout << "-s:\tstring to append\n";
			cout << "-u:\treplace spaces with underscores (y or n)\n";
			cout << "no arguments:\tinteractive mode\n";
			return 0;
		}
	}

	infile_name_string = "default";
	outfile_name_string = "default";
	append_string = "default";
	replace_spaces = -1;

	infile_name = new char[1000];
	outfile_name = new char[1000];

	for (i = 1; i < argc-1; i++)
	{
		tempstring1 = argv[i];
		tempstring2 = argv[i+1];
		if (tempstring1 == "-i")
			infile_name_string = tempstring2;
		if (tempstring1 == "-o")
			outfile_name_string = tempstring2;
		if (tempstring1 == "-s")
			append_string = tempstring2;
		if (tempstring1 == "-u")
		{
			if (tempstring2[0] == 'y' || tempstring2[0] == 'Y')
				replace_spaces = 1;
			if (tempstring2[0] == 'n' || tempstring2[0] == 'N')
				replace_spaces = 0;
		}
	}

	if (infile_name_string == "default")
	{
		cout << "Input Filename:\n";
		cin >> infile_name_string;	
		interactivemode = true;
	}

	if (outfile_name_string == "default")
	{
		cout << "\nOutput Filename:\n";
		cin >> outfile_name_string;
		interactivemode = true;
	}

	if (append_string == "default")
	{
		cout << "\nString to Append:\n";
		cin >> append_string;
		interactivemode = true;
	}

	if (replace_spaces == -1)
	{
		cout << "\nReplace spaces with underscores (y or n)?\n";
		cin >> query;
		if (query[0] == 'Y' || query[0] == 'y')
			replace_spaces = 1;
		else
			replace_spaces = 0;
		interactivemode = true;
	}

	for (i = 0; i < static_cast<int>(infile_name_string.length()); i++)
		infile_name[i] = infile_name_string[i];
	infile_name[i] = '\0';

	for (i = 0; i < static_cast<int>(outfile_name_string.length()); i++)
		outfile_name[i] = outfile_name_string[i];
	outfile_name[i] = '\0';

	cout << "\n\nInput File:\t" << infile_name;
	cout << "\nOutput File:\t" << outfile_name;
	cout << "\nAppend String:\t" << append_string;
	if (replace_spaces == 1)
		cout << "\nReplace Spaces:\tYes";
	else
		cout << "\nReplace Spaces:\tNo";

	if (interactivemode)
	{
		cout << "\n\nProceed? (y to proceed)\n";
		cin >> query;

		if (query != "y" && query != "Y")
		{
			cout << "\n\nEnter an integer to exit!!\n";
			cin >> i;
			return 0;
		}
	}

	cout << "\n\nProceeding...\n";

	// Load the query sequences and put them in the vector

	char *line = new char[200001];
	
	int linecounter = 0;
	int linereplacementcounter = 0;

	ifstream infile;
	ofstream outfile;
	string teststring;

	infile.open(infile_name);

	if (!infile.good())
	{
		cout << "\nNot a valid file!";
		if (interactivemode)
		{
			cout << "\nPress any key to exit!";
			cin >> i;
		}
		return 0;
	}

	char peeker = infile.peek();
	if (peeker != '>')
	{
		cout << "\nNot a valid fasta file!";
		if (interactivemode)
		{
			cout << "\nPress any key to exit!";
			cin >> i;
		}
		return 0;
	}

	outfile.open(outfile_name);

	while (!infile.eof())
	{
		infile.getline(line,200000);

		if (line[0] == '>' && linecounter % 2 == 0)
		{
			teststring = line;
			teststring = teststring + append_string;
			// replace spaces with underscores
			if (replace_spaces == 1)
			{
				for (i = 0; i < static_cast<int>(teststring.length()); i++)
						if (teststring[i] == ' ') teststring[i] = '_';
			}
			outfile << teststring << '\n';
			linereplacementcounter++;
		}
		else
		{
			if (line[0] != '\n' && line[0] != '\0')
				outfile << line << '\n';
		}
		linecounter++;

		if (linecounter % 100000 == 0)
			cout << "\n" << linecounter << " lines done!";
	}

	cout << '\n' << linecounter << " lines checked.";
	cout << '\n' << linereplacementcounter << " lines changed.\n";

	infile.close();
	outfile.close();

	delete[] line;
	delete[] infile_name;
	delete[] outfile_name;

	if (interactivemode)
	{
	  cout << "\n\nEnter an integer to exit!!";
	  cin >> i;
	}

	return 0;
}