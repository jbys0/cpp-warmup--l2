// =====================================================================
//  C++ WARM-UP  ·  African Olympiad Academy
//
//  The question descriptions are in README.md. Read them there.
//  This file holds the data, one worked example, and your answers.
//
//  BUILD AND RUN:   g++ -std=c++17 -Wall -o run warmup.cpp && ./run
//            or:    ./run.sh
//
//  Work on ONE question at a time. Write it, run it, check the output
//  against the README, commit it, move on.
// =====================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

/**
 * THE RECORD
 * One delivery: who brought it, how much, and what grade it was given.
 */
struct Delivery {
    string farmer;
    double kg;
    char   grade;
};


/**
 * THE DATA
 * Do not change these. Every expected answer in the README comes from exactly this data.
 */

// Q1 — one morning's weights, in the order they were weighed
vector<double> morningWeights = {
    45.5, 80.0, 12.0, -3.0, 66.5, 20.0, 31.0, 95.0, 50.0, 18.5, 0.0, 72.0
};

// Q2, Q3, Q4, Q7, Q8 — the day's logbook
vector<Delivery> logbook = {
    {"Keza",    45.5, 'A'},
    {"Bonu",    80.0, 'B'},
    {"Isanda",  20.0, 'A'},
    {"Keza",    12.0, 'C'},
    {"Onyinye", 66.5, 'B'},
    {"Karimi",  31.0, 'A'},
    {"Karimi",  31.0, 'A'},
    {"Keza",    18.5, 'B'},
    {"Bonu",    50.0, 'C'},
    {"Isanda",  20.0, 'A'},
    {"Onyinye", 72.0, 'A'}
};   // yes, one of these rows is in here twice. Q8 is about that.

// Q5 — records as the volunteers typed them, before any checking. Several of these are wrong. That is the point.
struct RawRecord {
    string id;
    string kg;        // text, because a volunteer can type anything
    char   grade;
};

vector<RawRecord> rawRecords = {
    {"F012", "45.5",  'A'},
    {"F7",   "20",    'A'},
    {"F033", "heavy", 'B'},
    {"F021", "0",     'C'},
    {"F044", "80",    'b'},
    {"F055", "",      'A'},
    {"F066", "31.5",  'D'},
    {"F077", "92",    'B'}
};

// Q6 — an Igisoro board. 16 pits, in sowing order.
//      Position 0 is unused so that board[1] really is pit 1.
vector<int> board = {0, 0, 0, 1, 0, 0, 4, 1, 0, 0, 2, 2, 0, 1, 5, 0, 0};


// ---------------------------------------------------------------------
//  A HELPER YOU MAY FIND USEFUL
// ---------------------------------------------------------------------
void printBoard(const vector<int> &b) {
    for (int i = 1; i <= 16; i++) cout << b[i] << " ";
    cout << "\n";
}
int findFarmer(const vector<Delivery> &log, string name){
    for(int i=0;i<log.size();i++){
        if(log[i].farmer==name){
            return i;
        }
    }
    return -1;
}

int main() {

    // =================================================================
    //  WORKED EXAMPLE  ·  not a question
    //
    //  This is the house style: walk the data once, keep what you need
    //  as you go, print at the end. Read it before you start Q1.
    //
    //  It answers: how many deliveries were grade A, and what was the
    //  heaviest single delivery in the whole logbook?
    // =================================================================

    int gradeACount = 0;
    Delivery heaviest = logbook[0];        // start from a REAL entry,
                                           // never from a made-up 0
    for (Delivery d : logbook) {
        if (d.grade == 'A') {
            gradeACount++;
        }
        if (d.kg > heaviest.kg) {
            heaviest = d;                  // keep the WHOLE record,
        }                                  // not just the number
    }

    cout << "=== Worked example ===\n";
    cout << "Grade A deliveries: " << gradeACount << "\n";
    cout << "Heaviest: " << heaviest.farmer << " with "
         << heaviest.kg << " kg\n\n";


    // =================================================================
    //  Q1  ·  THE WEIGHING SESSION          (see README)
    //  Uses: morningWeights
    // =================================================================
    int val=0,pos=0,run=0,main=run;
    double ttl=0,hev=morningWeights[0];
    for(int i=0; i<12;i++){
        ttl+=morningWeights[i];
        if(morningWeights[i]>0 and morningWeights[i]<=80){
            val+=1;
            run+=1;
        }
        else{
            if(run>main){
                main=run;
            }
            run=0;
        }
        if(morningWeights[i]>hev){
            hev=morningWeights[i];
            pos=i;
        }
    }
    if(run>main){
        main=run;
    }
    cout << "=== Q1 ===\n";
    cout<<"total: "<<ttl<<"\n";
    cout<<"valid: "<<val<<" outof 12"<<"\n";
    cout<<"Heaviest: "<<morningWeights[pos]<<" at position "<<pos<<"\n";
    cout<<"Longest valid run: "<<main<<"\n";




    cout << "\n";


    // =================================================================
    //  Q2  ·  GRADE SUMMARY                 (see README)
    //  Uses: logbook
    // =================================================================
    int a=0,b=0,c=0;
    double ak=0,bk=0,ck=0;
    char bav='A';
    double big;
    for(Delivery y:logbook){
        if(y.grade=='A'){
            a++;
            ak+=y.kg;
        }
        if(y.grade=='B'){
            b++;
            bk+=y.kg;
        }
        if(y.grade=='C'){
            c++;
            ck+=y.kg;
        }
    }
    big=ak/a;
    if(big < bk/b) {
        big=bk/b;
        bav='B';
    }
    if(big < ck/c) {
        big=ck/c;
        bav='C';
    }
    cout << "=== Q2 ===\n";
    cout<<"Grade A:"<< a <<" deliveries, "<<ak<<" kg total, "<<ak/a<<" kg average \n";
    cout<<"Grade B:" <<b <<" deliveries, "<<bk<<" kg total, "<<bk/b<<" kg average \n";
    cout<<"Grade C:"<< c <<" deliveries, "<<ck <<" kg total, "<<ck/c<<" kg average \n";
    cout<<"Best average: grade "<<bav<<"\n";





    cout << "\n";


    // =================================================================
    //  Q3  ·  WHO IS WHO                    (see README)
    //  Uses: logbook, and the findFarmer function you write below main
    // =================================================================

    cout << "=== Q3 ===\n";
    int q=findFarmer(logbook, "Isanda");
    int r=findFarmer(logbook, "Mukamana");
    cout<<"findFarmer(Isanda) ="<<q<<"\n";
    cout<<"findFarmer(Mukamana) ="<<r<<"\n";
    map<string,double> dev;
    map<string,double> freq;
    for(Delivery f:logbook){
        if(dev.find(f.farmer)==dev.end()){
            dev[f.farmer]=f.kg;
        }
        else{
            dev[f.farmer]+=f.kg;
        }
        if(freq.find(f.farmer)==dev.end()){
            freq[f.farmer]=1;
        }
        else{
            freq[f.farmer]+=1;
        }
    }
    double heav=0;
    string nam="";
    for(auto [farme,kgs]:dev){
        if(kgs>heav){
            heav=kgs;
            nam=farme;
        }
    }
    int mst=0;
    string na="";
    for(auto [farm,cnt]:freq){
        if(cnt>mst){
            mst=cnt;
            na=farm;
        }
    }
    cout<<"Most deliveries:"<<na<<"("<<mst<<")\n";
    cout<<"Most kg:"<<nam<<"("<<heav<<" kg)\n";

    cout << "\n";


    // =================================================================
    //  Q4  ·  PAYMENT RUN WITH A DAILY CAP  (see README)
    //  Uses: logbook, and the payment function you write below main
    // =================================================================

    cout << "=== Q4 ===\n";
    double pay=0;
    double rt=450.0;
    for(Delivery n:logbook){
        double fee;
        if(n.grade=='A'){
            fee=n.kg*rt;
            fee+=fee*0.1;
        }
        else if(n.grade=='B'){
            fee=n.kg*rt;
        }
        else if(n.grade=='C'){
            fee=n.kg*rt;
            fee-=fee*0.2;
        }
        if(pay>100000) fee= fee/2;
        pay+=fee;
        cout<<n.farmer <<" "<<n.kg<< " kg grade " <<n.grade<< "-> "<<fee<<"\n";
    }
    cout<<"Total paid: "<<pay<<"\n";




    cout << "\n";


    // =================================================================
    //  Q5  ·  THE VALIDATION REPORT         (see README)
    //  Uses: rawRecords
    // =================================================================

    cout << "=== Q5 ===\n";
    int acc=0, rej=0;
    double kil;
    for(RawRecord y:rawRecords){
        rej+=1;
        if(y.id[0]!='F'||y.id.size() < 4){
            cout<<y.id<<" REJECT - bad id\n";
            continue;
        }
        bool brk=false;
        for(int h=1;h<y.id.size();h++) {
            if(!isdigit(y.id[h])){
                brk=true;
                break;
            }
        }
        if(brk){
            cout<<y.id<<" REJECT - bad id\n";
            continue;
        }
        string emkg=y.kg;
        if(emkg.empty()){
            cout<<y.id<<" REJECT - weight missing\n";
            continue;
        }
        try{
            stod(y.kg);
        }
        catch(...){
            cout<<y.id<<" REJECT - weight not a number\n";
            continue;
        }
        kil=stod(y.kg);
        if(kil<=0 || kil>80){
            cout<<y.id<<" REJECT - weight out of range\n";
            continue;
        }
        char letter=toupper(y.grade);
        if(letter!='A'&& letter!='B' &&letter!='C'){
            cout<<y.id<<" REJECT - unknown grade\n";
            continue;
        }
        cout<<y.id<<" ACCEPTED\n";
        rej-=1;
        acc+=1;
    }
    cout<<acc<<" accepted, "<<rej<<" rejected";




    cout << "\n";

    // =================================================================
    //  Q6  ·  IGISORO: A FULL TURN          (see README)
    //  Uses: board
    // =================================================================

    cout << "=== Q6 ===\n";
    int laps=0;
    int i_pos=6;
    int hand=0;
    while (true){
        hand=board[i_pos];
        for(int i=i_pos+1;i<i_pos+hand+1;i++){
            if(i>16) i=16-i;
            board[i]+=1;
        }
        board[i_pos]=0;
        i_pos+=hand;
        if(i_pos>16) i_pos-=16;
        laps+=1;
        if(board[i_pos]<=1){
            break;
        }
        
    }
    cout<<"Final board: ";
    for(int i=1;i<board.size();i++){
        cout<<board[i]<<" ";
    }
    cout<<"\n";
    cout<<"Landed in pit "<<i_pos<<" after "<<laps<<" laps\n";

    
    // =================================================================
    //  STRETCH  ·  optional
    // =================================================================

    // =================================================================
    //  Q7  ·  SORT THE LOGBOOK              (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q7 ===\n";





    // =================================================================
    //  Q8  ·  SPOTTING DOUBLE-ENTRIES       (see README)
    //  Uses: logbook
    // =================================================================

    // cout << "=== Q8 ===\n";





    return 0;
}


// =====================================================================
//  FUNCTIONS YOU WRITE
//
//  C++ reads a file top to bottom, so a function must be DECLARED above
//  the place that calls it. These two are declared here at the bottom,
//  which main() cannot see — so move them ABOVE main(), or leave a
//  one-line declaration up there. Working that out is part of Q3.
// =====================================================================

// Q3:  return the position of the first delivery by this farmer,
//      or -1 if the farmer is not in the log at all.
//
// int findFarmer(const vector<Delivery> &log, string name) {
//
// }


// Q4:  what one delivery earns, before any cap is applied.
//      Grade A pays 10% above the rate, B pays the rate,
//      anything else pays 20% below it. The rate is 450.
//
// double payment(double kg, char grade) {
//
// }
