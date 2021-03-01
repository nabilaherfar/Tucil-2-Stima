/*  Nama    : Nabilah Erfariani
    NIM     : 13519181
    Kelas   : K-04
    Tugas Kecil 2 Strategi Algoritma
    Penerapan Decrease and Conquer
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

namespace std { };
using namespace std;

void topologicalsort(vector<vector<size_t> >& dag, vector<bool>& sudahexplored, size_t i, vector<size_t>& hasilsorting, size_t& jumlahderajat)
// melakukan proses topological sort
{
    sudahexplored[i] = true;

    size_t j = 0;
    while(j < dag[i].size()){
        //mencari vertex yang belum di explore
        if(sudahexplored[dag[i][j]] == false){
            topologicalsort(dag, sudahexplored, dag[i][j], hasilsorting, jumlahderajat);
        }
        j++;
    }

    //mengurangi jumlah derajat
    --jumlahderajat;

    //meletakkan derajat tersebut pada list
    hasilsorting[jumlahderajat] =i;

    return;
}

void exploredvertex (vector<vector<size_t> >& dag, vector<size_t>& hasilsorting)
//fungsi untuk mencari vertex yang tidak memiliki preferences
{

    vector<bool> sudahexplored(dag.size(), false);
    size_t jumlahderajat = dag.size();
    size_t i = 0;

    while(i < dag.size()){
        //mencari vertex yang belum di explore
        if(sudahexplored[i]==false){
            //melakukan topological sort
            topologicalsort(dag, sudahexplored, i, hasilsorting, jumlahderajat);
        }
        ++i;
    }

    //set jumlah derajat menjadi 0
    assert(jumlahderajat == 0);

    return;
}

istream& operator>> (istream& operatorassign, vector<vector<size_t> > & dag)
//mendefinisikan method operator
{
    // KAMUS
    size_t i = 0;
    size_t j = 0;

    //ALGORITMA
    operatorassign >> i; //membaca operator untuk i

    //melakukan resize untuk DAG
    dag.resize(i);

    //melakukan loop hingga panjang DAG
    while(operatorassign >> i >> j){

        --i;//decrement i
        --j;//decrement j

        //jika i dan j tidak sama
        if(i != j){
            dag[i].push_back(j);
        }
    }

    return operatorassign;
}

int main(int argc, char* argv[]){
    //Definisikan vektor
    vector<vector<size_t> > dag;

    //set nama file pada command line
    if(argc>1){
        ifstream myfile;
    
        //membuka file txt
        myfile.open(argv[1]);
        myfile >> dag;
        myfile.close();

    }

    //set jumlah simpul pada DAG / jumlah variabel pada DAG
    assert(dag.size() == 5);

    //definisikan vector
    vector<size_t> hasilsorting(dag.size(), 0);
    exploredvertex(dag, hasilsorting);

    cout << "Hasil Topological Sort: " << endl;

    //melakukan loop sebanyak panjang DAG
    for (size_t i =0; i<hasilsorting.size(); ++i){
        //menampilkan hasil topological sort
        cout << "Semester " << i+1 << " : " << (hasilsorting[i]+1) << "\n";
    }
    cout << endl;
    return 0;
}