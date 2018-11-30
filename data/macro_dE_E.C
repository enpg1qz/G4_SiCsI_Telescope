
#include "TLatex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

/*

std::vector<std::string> StringSplit(std::string str)
{
    std::string pattern="\t\n\v\f\r #";
    std::string::size_type pos;
    std::vector<std::string> result;

    str+=pattern;//扩展字符串以方便操作
    std::string::size_type size=str.size();

    for(std::string::size_type i=0; i<size; i++)
    {
        pos=str.find_first_of(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            if(s!=""){result.push_back(s);}
            i=pos;
        }
    }
    return result;
}

void ReadData(std::fstream& theFile,std::vector<std::vector<std::string> >& result)
{
  result.clear();
	std::string str;
	while(getline(theFile,str)){
		if(str.find_first_not_of("\t\n\v\f\r ")!=std::string::npos){
			if(str[0]!='#'){
				result.push_back(StringSplit(str));
			}
		}
	}
}
*/

// Reads the points from a file and produces a simple graph.
int macro_dE_E(){

  auto c=new TCanvas("c","my canvas",1200,800);
  //auto mg = new TMultiGraph();


  TGraph graph_proton("./proton-1540-E-dE-100000.txt", "%lg %lg");
  graph_proton.SetTitle(" dE - E; E / MeV; dE / MeV ");
	//graph_proton.SetTitle(" H1   E - dE; E  MeV; dE  MeV ");
	graph_proton.GetXaxis()->SetRangeUser(0,100);//qz
	//graph_proton->SetLineWidth(2);
	//graph_proton->SetMarkerSize(2);
	graph_proton.SetMarkerColor(2); ///0-49
	///graph_proton->SetLineColor(11);
	graph_proton.DrawClone("AP");
  ///mg->Add(&graph_proton);

  TGraph graph_deuteron("./deuteron-1540-E-dE-100000.txt", "%lg %lg");
  //graph_proton.SetTitle(" p   dE - E; E  MeV; dE  MeV ");
	//graph_deuteron.SetTitle(" H2   E - dE; E  MeV; dE  MeV ");
	//graph_deuteron.GetXaxis()->SetRangeUser(0,100);//qz
	//graph_proton->SetLineWidth(2);
	//graph_proton->SetMarkerSize(2);
	graph_deuteron.SetMarkerColor(3); ///0-49
	///graph_proton->SetLineColor(11);
	graph_deuteron.DrawClone("P");   ///// superimpose the second graph by leaving out the axis option "A"
  ///mg->Add(&graph_deuteron);

  TGraph graph_triton("./triton-1540-E-dE-100000.txt", "%lg %lg");
  graph_triton.SetMarkerColor(4); ///0-49
  ///graph_triton->SetLineColor(11);
  graph_triton.DrawClone("P");   ///// superimpose the second graph by leaving out the axis option "A"

  TGraph graph_He3("./He3-1540-E-dE-100000.txt", "%lg %lg");
  graph_He3.SetMarkerColor(7); ///0-49
  ///graph_He3->SetLineColor(11);
  graph_He3.DrawClone("P");   ///// superimpose the second graph by leaving out the axis option "A"

  TGraph graph_alpha("./alpha-1540-E-dE-100000.txt", "%lg %lg");
  graph_alpha.SetMarkerColor(30); ///0-49
  ///graph_alpha->SetLineColor(11);
  graph_alpha.DrawClone("P");   ///// superimpose the second graph by leaving out the axis option "A"

  TGraph graph_proton_LISE("./SSD1_H1-1105.txt", "%*lg %*lg %lg %lg");
  graph_proton_LISE.SetMarkerColor(1); ///0-49
  graph_proton_LISE.DrawClone("P");   ///// superimpose the second graph by leaving out the axis option "A"

  TGraph graph_deuteron_LISE("./SSD1_H2-1105.txt", "%*lg %*lg %lg %lg");
  graph_deuteron_LISE.SetMarkerColor(1); ///0-49
  graph_deuteron_LISE.DrawClone("P");

  TGraph graph_triton_LISE("./SSD1_H3-1105.txt", "%*lg %*lg %lg %lg");
  graph_triton_LISE.SetMarkerColor(1); ///0-49
  graph_triton_LISE.DrawClone("P");

  TGraph graph_He3_LISE("./SSD1_He3-1105.txt", "%*lg %*lg %lg %lg");
  graph_He3_LISE.SetMarkerColor(1); ///0-49
  graph_He3_LISE.DrawClone("P");

  TGraph graph_alpha_LISE("./SSD1_He4-1105.txt", "%*lg %*lg %lg %lg");
  graph_alpha_LISE.SetMarkerColor(1); ///0-49
  graph_alpha_LISE.DrawClone("P");


	// Draw the Legend
 	//TLegend leg(.1,.7,.3,.9,"Lab. Lesson 2");
 	TLegend leg(.7,.7,.9,.9);
	leg.SetFillColor(0);
  leg.AddEntry(&graph_proton,"proton","p");
  leg.AddEntry(&graph_deuteron,"deuteron","p");
  leg.AddEntry(&graph_triton,"triton","p");
  leg.AddEntry(&graph_He3,"He3","p");
  leg.AddEntry(&graph_alpha,"alpha","p");
	leg.AddEntry("","LISE","p");
  leg.DrawClone("Same");
  ///mg->Add(&leg);


  ///mg->Draw("ap");

	c->Print("dE-E-1540.pdf");

//	delete c;
///  delete [] x;
///  delete [] y;
	return 0;
}
