//
//  sessionization.cpp
//  SMikaiel_coding_challenge
//
//  Created by Samantha Mikaiel on 3/31/18.
//

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //initializations
    string ip,ipdate,iptime,ipcik;
    int inactivityperiod, line = 0;
    int count = 1;
    int i, ipcheck;
    vector <vector <string> > data;
    vector<int>::iterator ipfind;
    string ipdatefirst = "0";
    
    //read in the input files
    ifstream x("input/inactivity_period.txt");
    x >> inactivityperiod;
    ifstream input("input/log.csv");
    if (!input) { cout << "file not read "<< endl;    }
    ofstream output ("output/sessionization.txt");
    
    while (input)
    {
        string s;
        if (!getline( input, s )) break;
        istringstream ss( s );
        vector <string> single_visit;
        vector <string> visit;
        while (ss)
        {
            string s;
            if (!getline( ss, s, ',' )) break;
            single_visit.push_back(s);
        }
        if (line >0)
            {
               // Organize Data
                ip = single_visit[0];
                ipdate = single_visit[1];
                iptime = single_visit[2];
                ipcik = single_visit[4];
                
                int h, m, s= 0;
                sscanf(iptime.c_str(), "%d:%d:%d", &h, &m, &s);
                int secs = h*3600 + m*60 + s;
                if (line == 1) //if midnight is passed need to add a day to the seconds
                {ipdatefirst = ipdate;}
                else
                {
                    if (ipdate != ipdatefirst)
                    {secs = secs + (24*3600);}
                }
                
                visit.push_back(ip); // [0] = ip address
                visit.push_back(ipdate); // [1] = date accesssed in yyyy-mm-dd
                visit.push_back(iptime); // [2] = time accesssed in hh:mm:ss
                visit.push_back(ipcik); // [3] = cik
                visit.push_back(to_string(1)); // [4] = session counter
                visit.push_back (to_string(secs)); // [5] = first time accesssed in seconds
                visit.push_back(ipdate); // [6] = most recent date accesssed in yyyy-mm-dd
                visit.push_back(iptime); // [7] = most recent time accesssed in hh:mm:ss
                visit.push_back (to_string(secs)); // [8] = most recent time accesssed in seconds
    
        // Analyze Data
               if (line == 1)
                    {data.push_back(visit);} // Add first data point to sessions
                else
                {
                    if (secs<=inactivityperiod) // When the run time is less than or = to inactivity period, all data is checked
                    {
                        ipcheck = 0; // flag on if ip has visited before
                        for (i=0; i<=data.size()-1;i++) //for every saved session
                        {
                            if (find (data[i].begin(), data[i].end(), ip) != data[i].end()) //if ip address has visited before
                            {
                                count = stoi(data [i][4]);
                                count ++;
                                data [i][4] = to_string(count); //increase session counter
                                data [i][6] = visit [6];
                                data [i][7] = visit [7];
                                data [i][8] = visit [8]; // update the last accecced time
                                ipcheck=1; //flag that ip has been visited before
                            }
                        }
                        if (!ipcheck) {data.push_back(visit);} // if ip has not been visited before, add to sessions
                    }
                    else // if run time is greater than inactivity period
                    {
                        ipcheck = 0;
                        for (i=0; i<=data.size()-1;i++) //run through all saved sessions
                        {
                            if (secs - stoi(data[i][8]) > inactivityperiod) //if passed time is greater than inactivity period
                            {
                                output << data [i][0] << "," << data [i][1] << " " <<  data [i][2] << "," << data [i][6] << " " <<  data [i][7] << "," << stoi(data [i][8]) - stoi(data [i][5]) +1 << "," << data [i][4] << endl; //output the session //add 1 to duration because upper bound included
                                cout << data [i][0] << "," << data [i][1] << " " <<  data [i][2] << "," << data [i][6] << " " <<  data [i][7] << "," << stoi(data [i][8]) - stoi(data [i][5])+1 << "," << data [i][4] << endl; //output the session
                                data.erase (data.begin() + i); //erase session so if ip address visits again it will be a new session
                                i--;
                            }
                            else // if time passed is less than or = to inactivity period
                            {
                                if (find (data[i].begin(), data[i].end(), ip) != data[i].end()) //if ip address has visited before
                                {
                                    count = stoi(data [i][4]);
                                    count ++;
                                    data [i][4] = to_string(count); //increase session counter
                                    data [i][6] = visit [6];
                                    data [i][7] = visit [7];
                                    data [i][8] = visit [8]; // update the last accecced time
                                    ipcheck=1; //flag that ip has been visited before
                                }
                            }
                        }
                        if (!ipcheck) {data.push_back(visit);}
                    }
                }
            }
        line++;
    }
    for (i=0; i<=data.size()-1;i++) //run through all saved sessions
    {
        output << data [i][0] << "," << data [i][1] << " " <<  data [i][2] << "," << data [i][6] << " " <<  data [i][7] << "," << stoi(data [i][8]) - stoi(data [i][5])+1 << "," << data [i][4] << endl; //output the session
        cout << data [i][0] << "," << data [i][1] << " " <<  data [i][2] << "," << data [i][6] << " " <<  data [i][7] << "," << stoi(data [i][8]) - stoi(data [i][5])+1 << "," << data [i][4] << endl; //output the session
        }
    output.close();
}
