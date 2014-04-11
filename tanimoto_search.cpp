#include <iostream>
#include <openbabel/obconversion.h>
#include <openbabel/mol.h>
#include <openbabel/obiter.h>
#include <openbabel/groupcontrib.h>
#include <openbabel/descriptor.h>
#include <openbabel/parsmart.h>
#include <openbabel/fingerprint.h>
#include <openbabel/babelconfig.h>
#include <openbabel/plugin.h>
#include <openbabel/mol.h>
#include <vector>
#include <algorithm>
#include <iosfwd>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace OpenBabel;
using namespace std; 

//-------------------------------------------
//Take 2 std::vector<unsined int> and do a bitwise comparison to get the tanimoto index
double Calculate_Tanimoto (vector<unsigned int> vec1, vector<unsigned int> vec2) {
    int andbits=0, orbits=0;
    unsigned int i;
    for (i=0;i<vec1.size();++i)
    {
      int andfp = vec1[i] & vec2[i];
      int orfp = vec1[i] | vec2[i];
      for(;andfp;andfp=andfp<<1)
        if(andfp<0) ++andbits;
      for(;orfp;orfp=orfp<<1)
        if(orfp<0) ++orbits;
    }
	return (double)andbits/(double)orbits;
}
//-------------------------------------------

int main (int argc, char **argv) 
{
bool display = false;

if (argc < 2)
{
cout << "Give me more files" << endl;
exit(EXIT_FAILURE);
}

if(display) for (int i = 1;i<argc;i++)
	cout << "Argument " << i << " " << argv[i] << endl;

//decleare 2 bit vectors
vector<unsigned int> fp1;
vector<unsigned int> fp2;

//Declare some variables
OpenBabel::OBMol mol1, mol2;
//Read from cin and write to cout
OpenBabel::OBConversion obconversion(&cin,&cout);

obconversion.SetInAndOutFormats("SDF","SMI");
obconversion.ReadFile(&mol1, argv[1]);
obconversion.ReadFile(&mol2, argv[2]);

///////////////////////////////
OBFingerprint *pFP1, *pFP2;
pFP1 = OBFingerprint::FindFingerprint("FP2"); 
pFP2 = OBFingerprint::FindFingerprint("FP2");
pFP1 -> GetFingerprint(&mol1, fp1);
pFP2 -> GetFingerprint(&mol2, fp2);
double result = Calculate_Tanimoto(fp1,fp2);
fp1.erase( fp1.begin(), fp1.end() ); //clear the vector after each molecule
fp2.erase( fp2.begin(), fp2.end() );
mol1.Clear();
mol2.Clear();

std::cout << "The Tanimoto score is " << result << std::endl;

return 0;
}





