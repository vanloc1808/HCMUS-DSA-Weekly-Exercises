#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef long long int64;
typedef int (*operation)(int, int);

class Utility {
public:
    static int gcd(int a, int b) {
        if(a == 0)
            return b;
        return gcd(abs(b) % abs(a), abs(a));
    }
    static int min(int a, int b) {
        if (a < b)
            return a;
        return b;
    }
    static int max(int a, int b) {
        if (a > b)
            return a;
        return b;
    }
};

operation op[] = {
    Utility::min,
    Utility::max,
    Utility::gcd,
};

class SparseTable {
private:
    int size;
    int height;
    vector<vector<int64>> table;
    vector<int64> pow2;
    int f;

    void gen2Pow() {
        // Already generated
        if(pow2.size() > 0) return;

        int64 temp = 1;
        for(int i = 0; i < height; i++) {
            pow2.push_back(temp);
            temp *= 2;
        }
    }
public:
    void make(const vector<int64> &arr, int f) {
        size = arr.size();
        height = log2(size) + 1;
        // Already make
        if(table.size() > 0)
            return;
        gen2Pow();
        // Initialize table
        for(int i = 0; i < height; i++) {
            table.push_back(vector<int64>(size));
        }
        // Begin algorithm
        for(int i = 0; i < size; i++)
            table[0][i] = arr[i];
        for(int i = 1; i < height; i++)
            for(int j = 0; j < size - pow2[i - 1] ; j++)
                table[i][j] = op[f](table[i - 1][j], table[i - 1][j + pow2[i - 1]]);
        // Saved type
        this->f = f;
    }
    int query(int lowerBound, int upperBound) {
        lowerBound = Utility::max(lowerBound, 0);
        upperBound = Utility::min(upperBound, size - 1);
        int k = log2(upperBound - lowerBound);
        return op[f](table[lowerBound][k], table[upperBound - pow2[k]][k]);
    }
    bool save(string fileName) {
        fstream ofs(fileName, ios::out);
        ofs << f << "\n";
        // Save size of array & table height
        ofs << size << " " << height << "\n";
        for(auto row : table) {
            for(auto i: row) {
                ofs << i << " ";
            }
            ofs << "\n";
        }
        ofs.close();
        return true;
    }
    bool load(string fileName) {
        fstream ifs(fileName, ios::in);
        if(!ifs.is_open()) {
            cerr << "Cannot read file!\n";
            return false;
        }
        ifs >> f;
        // Load size, height and init table
        ifs >> size;
        ifs >> height;
        table = vector<vector<int64>>(height, vector<int64>(size));
        for (auto &row: table)
            for(auto &i: row)
                ifs >> i;
        ifs.close();
        return true;
    }
};

class Command {
protected:
    string tableName;
    SparseTable st;
public:
    Command(string tableName) 
        : tableName(tableName) {}
    virtual void execute() {}
};

class MakeCommand : public Command {
private:
    vector<int64> seq;
    string tableType;
public:
    MakeCommand(char* tableName, char* tableType, char** seq, size_t seqSize)
        : Command(string(tableName)) {
            this->tableType = string(tableType);
            for(int i = 0; i < seqSize; i++) 
                this->seq.push_back(atoi(seq[i]));
    }
    void execute() {
        int f = 0;
        if(tableType == "MIN")
            f = 0;
        else if(tableType == "MAX")
            f = 1;
        else if(tableType == "GCD")
            f = 2;
        else {
            cerr << "Invalid table type!\n";
            exit(1);
        }
        st.make(seq, f);
        st.save(tableName + ".st");
    }
};

class QueryCommand : public Command {
private:
    int lowerBound;
    int upperBound;
public:
    QueryCommand(char* tableName, char* lowerBound, char* upperBound)
        : Command(string(tableName)) {
            this->lowerBound = atoi(lowerBound);
            this->upperBound = atoi(upperBound);
        }
    void execute() {
        if(st.load(tableName + ".st")) {
            cout << st.query(lowerBound, upperBound) << "\n";
        }
    }
};

Command* cmd = nullptr;

void parseArgument(int argc, char** argv) {
    if(argc < 5 
        || (strcmp(argv[1], "make") && strcmp(argv[1], "query"))) {
        cerr << "Invalid argument!\n";
        cout << "Supported argument: \n";
        cout << "\t file make [Table_name] [Table_type] [Sequence]\n";
        cout << "\t file query [Table_name] [Lower_bound] [Upper_bound]\n";
        exit(1);
    }

    if(!strcmp(argv[1], "make")) {
        cmd = new MakeCommand(argv[2], argv[3], argv + 4, argc - 4);
    } else {
        cmd = new QueryCommand(argv[2], argv[3], argv[4]);
    }
}

int main(int argc, char** argv) {
    parseArgument(argc, argv);
    cmd->execute();
    delete cmd;
    return 0;
}