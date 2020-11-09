#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<stdlib.h>

using namespace std;
//
//
//KnM
vector<vector<int>>
graphM_complete( int n )
{
    //  Initialize adjacency matrix    to 0
    vector<vector<int>> KnM( n, vector<int>( n, 0 ) );
    //  Fill adjacency matrix taking into account all the possible edges i-k
    for( int i=0; i<n; i++ )
        for (int k = i+1; k<n; k++)
            KnM[i][k] = KnM[k][i]=1;
    return KnM;
}
//
//CN
vector<vector<int>>
graphM_cycle( int n )
{
    vector<vector<int>> CnM( n, vector<int>( n, 0 ) );
    for( int i=0; i<n-1; i++ )
        CnM[i][i+1] = CnM[i+1][i]=1;
    CnM[0][n-1]=CnM[n-1][0]=1;
    return CnM;
}
//
//SN
vector<vector<int>>
graphM_stars( int n )
{
    vector<vector<int>> SnM( n, vector<int>( n, 0 ) );
    for( int i=0; i<n-1; i++ )
        SnM[n-1][i] = SnM[i][n-1]=1;
    return SnM;
}
//
//WN
vector<vector<int>>
graphM_wheels( int n )
{
    vector<vector<int>> WnM( n, vector<int>( n, 0 ) );
    for( int i=0; i<n-1; i++ ){
        WnM[n-1][i] = WnM[i][n-1]=1;
        if(i<n-1)
            WnM[i][i+1] = WnM[i+1][i]=1;
    }
    return WnM;
}
//
//K
vector<vector<int>>
graphM_bipartits( int n1, int n2 )
{
    vector<vector<int>> KM( n1+n2, vector<int>( n1+n2, 0 ) );
    for( int i=0; i<n1; i++)
        for( int j=n1; j<n1+n2; j++)
            KM[j][i]=KM[i][j]=1;
    return KM;
}
//
//G
vector<vector<int>>
graphM_grids( int n1, int n2 )
{
    vector<vector<int>> GM( n1*n2, vector<int>(  n1*n2, 0 ) );
    for (int i=0; i<n1; i++){
        for (int j=0; j<n2; j++){
            int v = i*n2 + j;
                if (j < n2-1)
                    GM[v][v+1] = GM[v+1][v] = 1;
                if (i < n1-1)
                    GM[v][n2+v] = GM[v+n2][v] = 1;
        }
    }
    for(int i=n1+n2; i<n1*n2-1; i++)
        GM[i][i+1]=GM[i+1][i]=1;
    for(int i=n2-1; i<(n1-1)*n2; i+=n2){
        GM[i][i+n2]=GM[i+n2][i]=1;
    }
    return GM;
}
//
//
//Comprovació de que dos grafs son iguals
//
bool test_equal (vector<vector<int>> &M1, vector<vector<int>> &M2){
    int n1=M1.size();
    int n2=M2.size();
    if(n1!=n2)
        return false;
    for(int i=0; i<n1; i++)
        for(int j=0; j<=i; j++)
            if(M1[i][j]!=M2[i][j])
                return false;
    return true;
    
}
//
//
//Comprovar que una permutacio donada es un isomorfisme entre dos grafs.
//
bool Test_P_Isomorphism (vector<vector<int> >&M1, vector<int>&P, vector<vector<int> >& M2)
{
    int n1=M1.size(), n2=M2.size(), n=P.size();
    if(n1!=n || n2!=n)
        return false;
    for(int i=0; i<n; i++)
        for(int k=0; k<n; k++)
            if(M1[i][k]!=M2[P[i]][P[k]])
                return false;
    return true;
}
//
//
//Comprovar que P es un automorfisme
//
bool Test_P_Automorphism (vector<vector<int> >&M, vector<int>& P)
{
    return Test_P_Isomorphism(M, P, M);
}
//
//
//Comprovar que dos grafs són isomorfs  comprovan totes les posibles permutacions fins que almenys en trobi una.
//
bool Test_Isomorphism (vector<vector<int> >& M1, vector<vector<int> >&M2)
{
    int n1=M1.size(), n2=M2.size();
    if(n1!=n2)
        return false;
    vector<int> P(n1);
    for(int i=0; i<n1; i++)
        P[i]=i;
    do{
        if(Test_P_Isomorphism(M1,P,M2))
            return true;
    }while(next_permutation(P.begin(), P.end()));
    return false;
}
//
//
//Dona una permutació aleatòria
//
vector<int>
Random_Permutation(int n){
    vector<int> P(n);
    vector<bool> B(n,false);
    for(int i=0; i<n; i++){
        int r=rand()%(n-i);
        for(int k=0; k<=r; k++){
            if(B[k]) r++;
            
        }
        P[i]=r;
        B[r]=true;
        }
    return P;
}
//
//
//Crea una matriu adjacent amb els vèrtex permutats
//
vector<vector<int>>
Matriu_Permutada(vector<int >&P, vector<vector<int> >& M1){
    int n=P.size();
    vector<vector<int>> M(n, vector<int>(n,0)) ;
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            M[i][j]=M1[P[i]][P[j]];
            M[j][i]=M[i][j];
        }
    }
    return M;
}
//
//Funció que troba si dos grafs són isomorf.
//
int Isomorphisms (vector<vector<int> >& M1,vector<vector<int> >& M2, ofstream& fout)
{
    int n1=M1.size(), n2=M2.size();
    if(n1!=n2)
        return 0;
    vector<int> P(n1);
     for(int i=0; i<n1; i++){
         P[i]=i;
     }
    int ison=0;
    do{
        if(Test_P_Isomorphism (M1,P,M2)){
            fout<< "Isomorfisme " << ++ison << " :   ";
            for(int i=0; i<n1; i++)
                fout<< "\t" << P[i];
            fout << endl;
            
        }
    }while(next_permutation(P.begin(), P.end()));
    fout<< endl;
    if(ison)
     fout << "ISOMORFISMES: "<< ison << " isomorfismes trobats" << endl;
    else
     fout << "No isomòrfics." << endl;
return ison;
}
//
//Escriu tots els automorfismes
int Automorphisms(vector<vector<int> >&M, ofstream& fout){
    int vn=M.size();
    vector<int> P(vn);
    vector<int> O(vn);
    for(int vi=0; vi<vn; vi++){
        P[vi]=vi;
        O[vi]=vi;
    }
    int auton=0;
    do{
        if(Test_P_Automorphism (M,P)){
            fout<< "Automorfismes " << ++auton << " :   ";
            //Merge orbits
            for(int vi=0; vi<vn; vi++){
                fout<< "\t" << P[vi];
                if(O[vi]<O[P[vi]])
                    O[P[vi]]=O[vi];
                else if (O[P[vi]]<O[vi])
                    O[vi]=O[P[vi]];
            }
        fout << endl;
            
        }
    }while(next_permutation(P.begin(), P.end()));
    fout<< endl;
    fout << "AUTOMORFISMES: "<< auton << " automorfismes trobats." << endl;
    fout<< endl;
    //Escribim les orbites
    fout << "Les orbites són: " << endl;
    for(int i=0; i<vn; i++){
        fout << O[i] << "\t";
    }
    fout<<endl;
    //Escrivim totes les classes d'equivalència juntes
    vector<bool> B(vn,false);
    int k=0;
    for(int i=0; k<vn ; i++){
        if(B[i]==false){
            fout<<endl;
            fout << "L'òrbita associada a " << O[i] << " és: ";
        }
        for(int j=0; j<vn; j++){
            if(O[j]==P[i]){
                fout << j <<" ";
                B[j]=true;
                k++;
            }
        }
    }
    fout<< endl;
    return auton;
}
//
//  Read SIMPLE graph from file fname of edges to adjacency matrix
//
//  IMPORTANT: This function should be adapted to multigraphs
vector<vector<int>>
graphM_read( string fname )
{
    ifstream fin;
    fin.open( fname.c_str() );
    if( fin.fail() ) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit( 1 );
    }
    // Read vertices and edges numbers
    int n, m;
    fin >> n >> m;
    // Initialize adjacency matrix    to 0
    vector<vector<int>> M( n, vector<int> (n, 0) );
    // Fill adjacency matrix taking into account all the edges u-v
    for( int j=0; j<m; j++) {
        int u, v;
        fin >> u >> v;
        M[u][v]++;
        M[v][u]++;
    }
    return M;
}
//
//  Write SIMPLE graph from adjacency matrix to file stream
//  - vertices and edges numbers
//  - adjacency matrix
//  - edges
//  - sorted degrees
//
//  IMPORTANT: This function has a bug that must be corrected
//  IMPORTANT: This function should be adapted to multigraphs
void
graphM_write( vector<vector<int>>& M, ofstream& fout )
{
    //  Vertices number
    int n = M.size();
    //  Count edges number from adajacency matrix
    int m = 0;
    for( int i = 0; i < n; i++ ){
        for( int k = 0; k < i+1; k++ ){
            if(i==k) m = m +(M[i][i]/2);
            else m = m + M[i][k];
        }
    }
    //  Write vertices and edges numbers
    fout << "Graph with " << n << " vertices and " << m << " edges " << endl;
    //  Write adjacency matrix
    fout << "Adjacency matrix" << endl;
    for( int i=0; i<n; i++ )  {
        for( int k=0; k<n; k++ )
            fout << "\t" << M[i][k];
        fout << endl;
    }
    //  Write edges
    fout << "Edges" << endl;
    for( int i = 0; i < n; i++){
        for( int k = 0; k < i; k++)
            for(int j=0; j<M[i][k]; j++)
                    fout << i << " " << k << endl;
        for(int j=0; j<M[i][i]/2; j++)
            fout << i << " " << i << endl;
    }
    //  Count degrees
    vector<int> deg( n );
    for( int i = 0; i < n; i++ ) {
            deg[i] = 0;
        for (int k = 0; k < n; k++){
            deg[i] += M[i][k];
        }
    }
     
    //  Write sorted degrees sequence
    fout << "Degrees sequence" << endl;
    for( int i = 0; i < n; i++ ) {
        fout << deg[i] << " ";
    }
    fout << endl;
    //  Sort degrees sequence
    sort( deg.begin(), deg.end() );
    //  Write sorted degrees sequence
    fout << "Sorted degrees sequence" << endl;
    for( int i = 0; i < n; i++ )
        fout << deg[i] << " ";
    fout << endl;
}
//
//
//
int
main()
{
   ofstream fout;
    //  graph0.in
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph0.out");
    vector<vector<int>> M0 = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph0.in");
    graphM_write( M0, fout );
    fout.close();
    //
    //
    //  graph1.in
    //
    
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph1.out");
    vector<vector<int>> M1 = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph1.in");
    graphM_write( M1, fout );
    fout.close();
    //
    //
    //  graph2.in
    //
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph2.out");
    vector<vector<int>> M2 = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph2.in");
    graphM_write( M2, fout );
    fout.close();
    //
    //
    //  graph3.in
    //
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph3.out");
    vector<vector<int>> M3 = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph3.in");
    graphM_write( M3, fout );
    fout.close();
    //
    //
    //EXERCICI 2
    //
    //
    //  C8
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/C8.out");
    vector<vector<int>> MC8 = graphM_cycle( 8 );
    graphM_write( MC8, fout );
    fout<< endl;
    //Anex exercici 7
    Automorphisms(MC8, fout);
    fout.close();
    //
    //  S8
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/S8.out");
    vector<vector<int>> MS8 = graphM_stars( 8 );
    graphM_write( MS8, fout );
    fout<< endl;
    //Anex exercici 7
    Automorphisms(MS8, fout);
    fout.close();
    //
    //  W8
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/W8.out");
    vector<vector<int>> MW8 = graphM_wheels( 8 );
    graphM_write( MW8, fout );
    fout<< endl;
    //Anex exercici 7
    Automorphisms(MW8, fout);
    fout.close();
    //
    //  K8
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/K8.out");
    vector<vector<int>> MK8 = graphM_complete( 8 );
    graphM_write( MK8, fout );
    fout<< endl;
    //Anex exercici 7
    Automorphisms(MK8, fout);
    fout.close();
    //
    //  K5_3 i K3_5
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/K5_3.out");
    vector<vector<int>> MK5_3 = graphM_bipartits( 5 , 3 );
    vector<vector<int>> MK3_5 = graphM_bipartits( 3 , 5 );
    fout<< "K5_3" << endl;
    graphM_write( MK5_3, fout );
    fout<< endl;
    fout<< "K3_5" << endl;
    graphM_write( MK3_5, fout );
    fout<< endl;
    //Anex exercici 7
    fout<< "PER A K3_5" << endl;
    Automorphisms(MK3_5, fout);
    fout<<endl;
    fout<< "PER A K5_3" << endl;
    Automorphisms(MK5_3, fout);
    fout<<endl;
    fout<< "ISOMORFISMES ENTRE A K5_3 I K3_5" << endl;
    Isomorphisms(MK3_5, MK5_3, fout);
    fout.close();
    //
    //G3_3
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/G3_3.out");
    vector<vector<int>> MG3_3 = graphM_grids( 3 , 3 );
    graphM_write( MG3_3, fout );
    fout<< endl;
    //Anex exercici 7
    Automorphisms(MG3_3, fout);
    fout.close();
    //
    //G4_2 i G2_4
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/G4_2.out");
    vector<vector<int>> MG4_2 = graphM_grids( 4 , 2 );
    vector<vector<int>> MG2_4 = graphM_grids( 2 , 4 );
    fout<< "G4_2" << endl;
    graphM_write( MG4_2, fout );
    fout<< endl;
    fout<< "G2_4" << endl;
    graphM_write( MG2_4, fout );
    fout<< endl;
    //Anex exercici 7
    fout<< "PER A G4_2" << endl;
    Automorphisms(MG4_2, fout);
    fout<<endl;
    fout<< "PER A G2_4" << endl;
    Automorphisms(MG2_4, fout);
    fout<<endl;
    fout<< "ISOMORFISMES ENTRE A G2_4 I G4_2" << endl;
    Isomorphisms(MG4_2, MG2_4, fout);
    fout.close();
    //
    //EXERCICI 3
    //
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/Exercici3.out");
    fout << "Apartat a)" << endl;
    if(test_equal(M1, M2)==true)
        fout << "El graf 1 i el 2 són iguals." << endl;
    else
        fout << "El graf 1 i el 2 no són iguals." << endl;
    //
    fout<< endl;
    fout << "Apartat b)" << endl;
    vector<int> P0 = {1,2,3,0};
    if(Test_P_Isomorphism (M1, P0, M3)==true)
        fout << "(1,2,3,0) és un isomorfisme dels grafs 1 i el 3." << endl;
    else
        fout << "(1,2,3,0) no és un isomorfisme dels grafs 1 i el 3." << endl;
    //
    fout<< endl;
    fout << "Apartat c)" << endl;
    if(Test_P_Automorphism(M1, P0)==true)
        fout << "(1,2,3,0) és automorfisme amb el graf 1." << endl;
    else
        fout << "(1,2,3,0) no és automorfisme amb el graf 1." << endl;
    //
    fout<< endl;
    fout << "Apartat d)" << endl;
    vector<int> P1 = {5,3,2,4,1,0,7,6};
    if(Test_Isomorphism(MK5_3, MK5_3)==true)
        fout << "(5,3,2,4,0,7,6) és isomorfisme entre els grafs K5_3 i K3_5" <<endl;
    else
         fout << "(5,3,2,4,0,7,6) no és isomorfisme entre els grafs K5_3 i K3_5" <<endl;
    fout.close();
    //
    //
    //EXERCICI 4
    //
    //
    srand((unsigned) time(NULL));
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/Exercici4.out");
    vector<int> P = Random_Permutation(8);
    vector<vector<int>> MP = Matriu_Permutada(P, MK3_5);
    graphM_write(MP, fout);
    if(Test_Isomorphism(MP, MK3_5))
        fout << "Són isomorfs com volíem comprovar." <<endl;
    else
        fout << "Programa mal fet." <<endl;
    fout.close();
    //
    //
    //EXERCICI 6
    //
    //
    fout.open("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph8.out");
    //
    //Graph 8A
    vector<vector<int>> M8A = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph8A.in");
    fout << "Graf 8A" <<endl;
    vector<vector<int>> M8B = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph8B.in");
    Automorphisms(M8A, fout);
    fout<< endl;
    //
    //Graph 8B
    fout << "Graf 8B" <<endl;
    Automorphisms(M8B, fout);
    fout<< endl;
    //
    //Graf 8A isomorf amb 8B?
    fout << "El graf 8A i el graf 8B són isomorfs." <<endl;
    fout<< endl;
    Isomorphisms(M8A, M8B, fout);
    fout<< endl;
    fout.close();
    //
    //Graph 10A
    vector<vector<int>> M10A = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph10A.in");
    fout << "Graph 10A" <<endl;
    Automorphisms(M10A, fout);
    fout<< endl;
    //
    //Graph 10B
    vector<vector<int>> M10B = graphM_read("/Users/xeniadomenech/Documents/UNIVERSITAT/Segon/Graphs/GPrc1_DomenechXenia.cpp/Programes/graph10B.in");
    fout << "Graph 10B" <<endl;
    Automorphisms(M10B, fout);
    fout<< endl;
    //
    //Graf 10A isomorf amb 10B?
    fout << "Isomorfismes entre graf 10A i graf 10B" <<endl;
    fout<< endl;
    Isomorphisms(M10A, M10B, fout);
    fout<< endl;
    fout.close();
    //
    //  Finish
    cout << endl << "Press enter to finish... ";
    cin.get();
}
