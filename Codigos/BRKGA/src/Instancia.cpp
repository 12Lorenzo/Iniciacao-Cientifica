#ifndef INSTANCIA_CPP
#define INSTANCIA_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <tuple>
#include <math.h>

#include "Instancia.h"

using namespace std;


/*Fazer mais um construtor para ler a instancias. Vai ser parecido com o recebeInst*/
Instancia::Instancia(string nomeArq){
    
    double coordX, coordY;
    int pos, tam, contLine = 0;
    
    string line;
    
    //cout << "\nlocal do arquivo: " << arq;
    ifstream myfile(nomeArq, ios::in); // ifstream = padrão ios:in

    //mostraInst("doublecenter", "doublecenter-1-n5.txt");

    if (myfile.is_open()) {
    
        while (! myfile.eof() ){ //enquanto end of file for false continua
            contLine++;
            getline (myfile,line); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
            
            //A função find ela retorna a primeira posição do caracter passado, a partir do ponto que começou a procurar
            //nesse caso ele vai procurar a primeira ocorrencia de " "(espaço) a partir da primeira posição da string
            pos = line.find(" ", 0);

            if(contLine == 2){
                
                //cout << "\nLin 2: " << line << "\n";
                velCam = stod(line);
                //cout << velCam;
            } else if(contLine == 4){
                
                //cout << "lin4: " << line.substr(0, pos);
                velDrone = stod(line);
            } else if(contLine == 6) {
                
                //cout << "lin6: " << line.substr(0, pos);
                numNos = stoi(line);
            } else if(line[0] != '/' && contLine > 7 && pos != EOF){
                //cout << "Frase";
                
                //cout << "\nPosicao: " << pos;
                //cout << "\nCoordenada X:" << line.substr(0, pos);
                coordX = stod(line.substr(0, pos));

                tam = pos+1;
                pos = line.find(" ", pos+1);
                //cout << "\nCoordeanada Y: " << line.substr(tam, pos-tam) << "\n";
                //A função substr retorna a string no intervalo passado
                coordY = stod(line.substr(tam, pos-tam));

                nos.push_back(make_pair(coordX, coordY));

            }
            
            //cout << "\nX: " << coordX << "Y: " << coordY;
        }
        myfile.close();
        //cout << "Numero de linhas do arquivo: " << contLine;
        //cout << "Velocidade Caminhao: " << velCam << "\nVelocidade Drone: " << velDrone << "\nNumero de nos: " << numNos << "\nCoordenada x: " << coordX << "\nCoordenada y: " << coordY;
        
    } else {
        cout << "Nao foi possivel abrir o arquivo";
    } 
}

Instancia::Instancia(){ }

Instancia::~Instancia(){ }

int Instancia::getNumNos(){
    return numNos;
}

double Instancia::getDist(int no1, int no2){
    double result;
    double cat1, cat2;
    cat1 = nos[no1].first - nos[no2].first;
    cat2 = nos[no1].second - nos[no2].second;

    result = sqrt(pow(cat1, 2) + pow(cat2, 2));

    return result;
}

void Instancia::formaMatDistancias(){
    vector<vector<double>>::iterator lin;
    vector<double>::iterator col;
    int i = 0, j = 0;
    for (lin = distancias.begin(); lin != distancias.end(); lin++){
        for(col = (*lin).begin(); col != (*lin).end(); col++){
            *col = getDist(nos[i].first, nos[i].second);
        }
    }
    
    
}

void Instancia::mostraMatDistancias(){
    vector<vector<double>>::iterator lin;
    vector<double>::iterator col;
    int i = 0, j = 0;
    for (lin = distancias.begin(); lin != distancias.end(); lin++){
        for(col = (*lin).begin(); col != (*lin).end(); col++){
            cout<< *col;
        }
        cout << endl;
    }
}

void Instancia::mostraInst(string nomeArq){
    int contLine = 0;
    string line;
    
    ifstream myfile(nomeArq, ios::in); // ifstream = padrão ios:in

    if (myfile.is_open()) {
    
        while (! myfile.eof() ){ //enquanto end of file for false continua
            contLine++;
            getline (myfile,line); // como foi aberto em modo texto(padrão) e não binário(ios::bin) pega cada linha

            cout << "Linha " << contLine << ": ";
            cout << line << endl;
            
        }
        myfile.close();

    } else {
        cout << "Unable to open file";
    }

}

pair<double, double> Instancia::formaPairCoord(double coordX, double coordY){
    pair<double, double> coords;

    get<0>(coords) = coordX;
    get<1>(coords) = coordY;

    return coords;
}

/*
vector<tuple<double, double, float>> Instancia::recebeInst(string nomeArq){
    //Função para ler informações da entradae criar nossas triplas que representam nós no grafo.
    
    double velDrone, velCam;
    double coordX, coordY;
    int pos, tam, numNos, contLine = 0, contNos = 0;

    vector<tuple<double, double, float>> grafo(0);
    
    string line;
    
    //cout << "\nlocal do arquivo: " << arq;
    ifstream myfile(nomeArq, ios::in); // ifstream = padrão ios:in

    //mostraInst("doublecenter", "doublecenter-1-n5.txt");

    if (myfile.is_open()) {
    
        while (! myfile.eof() ){ //enquanto end of file for false continua
            contLine++;
            getline (myfile,line); // como foi aberto em modo texto(padrão)
                             //e não binário(ios::bin) pega cada linha
            
            //A função find ela retorna a primeira posição do caracter passado, a partir do ponto que começou a procurar
            //nesse caso ele vai procurar a primeira ocorrencia de " "(espaço) a partir da primeira posição da string
            pos = line.find(" ", 0);

            if(contLine == 2){
                
                //cout << "\nLin 2: " << line << "\n";
                velCam = stod(line);
                //cout << velCam;
            } else if(contLine == 4){
                
                //cout << "lin4: " << line.substr(0, pos);
                velDrone = stod(line);
            } else if(contLine == 6) {
                
                //cout << "lin6: " << line.substr(0, pos);
                numNos = stoi(line);
            } else if(line[0] != '/' && contLine > 7 && pos != EOF){
                //cout << "Frase";
                
                //cout << "\nPosicao: " << pos;
                //cout << "\nCoordenada X:" << line.substr(0, pos);
                coordX = stod(line.substr(0, pos));

                tam = pos+1;
                pos = line.find(" ", pos+1);
                //cout << "\nCoordeanada Y: " << line.substr(tam, pos-tam) << "\n";
                //A função substr retorna a string no intervalo passado
                coordY = stod(line.substr(tam, pos-tam));

                grafo.push_back(formaTuplaCoord(contNos, coordX, coordY));

                contNos++;
            }
            
            //cout << "\nX: " << coordX << "Y: " << coordY;
        }
        myfile.close();
        //cout << "Numero de linhas do arquivo: " << contLine;
        //cout << "Velocidade Caminhao: " << velCam << "\nVelocidade Drone: " << velDrone << "\nNumero de nos: " << numNos << "\nCoordenada x: " << coordX << "\nCoordenada y: " << coordY;
        
    } else {
        cout << "Unable to open file";
    } 


   return grafo;
}
*/

void Instancia::printInst()
{

    cout << "Velocidade do caminhao: " << velCam << endl;
    cout << "Velocidade do drone: " << velDrone << endl;
    cout << "Numero de nos: " << numNos << endl;
    for (int i = 0; i < nos.size(); i++){
        
        cout << i << ": (" << nos[i].first << ", " 
             << nos[i].second << ")\n";
    }

    cout << endl;
}

#endif