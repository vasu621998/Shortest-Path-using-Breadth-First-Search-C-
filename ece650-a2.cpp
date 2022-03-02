// Compile with c++ ece650-a2.cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <regex>
#include <string>
using namespace std;

void BFS(int source, int destination, vector<vector<bool>>&matrix){
    //if(source == destination){
    //    cout<< source << endl;

    //}

    int n_vertices = (int)matrix.size();
    source = source - 1;
    destination = destination - 1; 
    if(source < n_vertices && destination < n_vertices){
        queue<int> q;
        vector<int> is_visit(n_vertices, false);
        vector<int> prev_visit(n_vertices, -1); 
        q.push(source);
        is_visit[source] = true;
        while (q.size() != 0){
            int node = q.front();
            q.pop();
            for(int i=0; i< (int)matrix[node].size(); i++){
                if(matrix[node][i] == 1 && !is_visit[i]){
                    q.push(i);
                    is_visit[i]=true;
                    prev_visit[i] = node;
                }
            }        
        }
        int last_node = destination;
        vector<int> route;
        while(last_node != -1){
            route.push_back(last_node);
            last_node = prev_visit[last_node];
        }
        reverse(route.begin(),route.end());
        ostringstream outputStream;
        vector<int> final_route;
        for(int i=0; i<route.size(); i++){
            route[i] = route[i] + 1;
        }


        if(route[0]==source + 1){
            copy(route.begin(), route.end()- 1, 
                ostream_iterator<int>(outputStream, "-"));
            outputStream << route.back();
            cout << outputStream.str() << endl;    
        } else {
            cout << "Error: No path exists between vertex " << source + 1  << " and " << destination + 1 << endl;
        }
        

    } else {
        cout << "Error: Invalid vertex specified" << endl;
    }
};

void reset(vector<vector<bool>>&matrix){
    // int ver = (int)matrix.size();
    for (int i =0; i < (int)matrix.size(); i++){
        for (int j =0; j < (int)matrix.size(); j++){
            matrix[i][j] = false;
        }
    }
}

void build_graph(string edges, vector<vector<bool>> &matrix){
    int mat_size = (int)matrix.size();
    // cout << mat_size;
    // Parsing edges 
    regex r("<.*?>");
    bool vertax_status = false;
    for(sregex_iterator iterator =
           sregex_iterator(edges.begin(), edges.end(), r);
       iterator != sregex_iterator(); iterator++){
           
           smatch match;           
           match = *iterator;
           string vertax_edges;
           vertax_edges = match.str(0);
           
           for(int i =0; i<match.length();i++){
               string v_edge = match[i];
               // cout << v_edge;
               int array[2] = {-1,-1};
               int vertax_id = 0;
               if(v_edge.length() > 0){
                    string edge_ver = v_edge.substr(1, v_edge.length() - 2);
                    // cout<< edge_ver <<endl;
                    char *edges_ptr = &edge_ver[0];
                    char *token = strtok(edges_ptr, ",");
                    while (token != NULL){
                        array[vertax_id] =  stoi(token) - 1;
                        //cout << stoi(token) << endl;
                        // cout << array[1] << endl;
                        vertax_id ++;
                        token = strtok(NULL, ",");
                        // cout << array[0] << endl;
                    }
                    // the adjacency matrix
                    if((array[0]>=0 && array[1]>=0) && (array[0]<mat_size && array[1]<mat_size) && array[0]!=array[1]){
                        matrix[array[0]][array[1]] = true;
                        matrix[array[1]][array[0]] = true;
                    }else{
                        vertax_status = true;
                        break;
                    }
                   
                  //for (int row = 1; row < matrix.size(); row++) {
                    //    cout << "\n";
                     //   for (int col = 1; col < matrix.size(); col++) {
                            
                      //       cout<< matrix[row][col]<< endl;
                    // }
                    //}                   
               }
           }

       }
    if(vertax_status){
        cout << "Error: Invalid edges" <<endl;
        reset(matrix);

    }

    //cout << "Matrix updated" <<endl;

};


void IntializeGraph(int vertice, vector<vector<bool>> &matrix) {
  int num_ver = (int)matrix.size();
  // Resize the matrix to size (vertex+1) X (vertex+1)
  for (int i = 0; i < num_ver; i++)
    matrix[i].resize(vertice);
  matrix.resize(vertice, vector<bool>(vertice));
  // Set all values in the matrix to false
  // Matrix printing

  for (int row = 0; row < (int)matrix.size(); row++) {
    for (int col = 0; col < (int)matrix.size(); col++) {
      matrix[row][col] = 0;
  //    cout<< matrix[row][col];
    }
  //  cout << "\n";
  }
  //cout << "Matrix generated" <<endl;
  //cout << matrix <<endl;

};


int main(int argc, char** argv) {
    // Test code. Replaced with your code
    // read from stdin until EOF

    static int init_vertice = 10;

    while (!std::cin.eof()) {

        std::string line;
        std::getline(std::cin, line);

        std::istringstream input(line);

        std::vector<string> nums;
        std::string str = "";
        while(input >> str){
            nums.push_back(str);
        }
        char cmd = nums.at(0)[0];
        static vector<vector<bool>> matrix(init_vertice, vector<bool>(init_vertice));
        string edges = "";
        switch(cmd){
            case 'V':
                {
                    //cout << "Inside V command" << endl;
                    if (nums.size() != 2) {
                        cerr << "Error: Invalid arguments for V command" << endl;
                        break;

                    }
                    else{
                        init_vertice = stoi(nums.at(1));
                        if(init_vertice <= 0){
                            cerr << "Error: Invalid V command" <<endl;
                            break;
                        }
                        else{
                            IntializeGraph(init_vertice, matrix);
                            break;
                        }


                    }
                   
                    
                }
            case 'E':
                {
                    if (nums.size() != 2) {
                        cout << "Error: Invalid arguments for E command" << endl;
                    }
                    else{
                        edges = nums.at(1);
                        build_graph(edges, matrix);

                    }
                   

                    //cout << "Inside E command" << endl;
                    break;
                }
            case 's':
                {
                    if (nums.size() != 3) {
                        cout << "Error: Invalid arguments for s command" << endl;
                    }
                    else{
                        BFS(stoi(nums.at(1)), stoi(nums.at(2)), matrix);
                        break;
                    }
                    //cout << "Inside s command" << endl;                    
                    
                }
            default:
                cout << "Error: Command not supported" << endl;      
                break;
    
            //case 'p':
            //    for (int i = 0; i < (int)matrix.size(); i++)
            //       {
            //        for (int j = 0; j < (int)matrix[i].size(); j++)
            //            {
            //                cout << matrix[i][j] << " ";
            //            }
            //        cout << endl;
            //        };
            //    break;

        }

        }

    
}
// V 5
// E {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}


