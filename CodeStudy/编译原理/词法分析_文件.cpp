#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream infile;    // 文件输入流
ofstream outfile;   // 文件输出流

vector<string> wordTable;	// 单词表
map<string, int> B;         // 保留字
map<string, int> Y;         // 运算符
map<char, int> J;           // 界符
map<char, int> y;           // 
string s1 , s2, s3 ;
int F; // 标记'/*''*/'注释

void Init() {
    B["const"] = B["var"] = B["procedure"] = B["begin"] = B["end"] = B["odd"] = B["if"] = B["then"] = B["call"] = B["while"] = B["do"] = B["read"] = B["write"] = 1; //保留字，13个 
    Y["+"] = Y["-"] = Y["*"] = Y["/"] = Y["<"] = Y["<="] = Y[">"] = Y[">="] = Y["#"] = Y["="] = Y[":="] = 1; //运算符，11个 
    y['+'] = y['-'] = y['*'] = y['/'] = y['<'] = y['>'] = y['='] = y['#'] = y[':'] = 1;
    J['('] = J[')'] = J[','] = J[';'] = J['.'] = 1; //界符，5个
    s1 = "//", s2 = "/*", s3 = "*/";
}

void LexicalAnalysis() {
    string input, word;
    Init();
    for (int line = 1; getline(infile, input); line++) {
        int f = 0; // 标记'//'注释
        for (int i = 0; input[i] != '\0'; i++) {
            // 去掉空格与'\t'
            while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
                i++;

            int numFlag = 0, letterFlag = 0, operatorFlag = 0, boundaryFlag = 0, illegalFlag = 0;
            int j1 = i, j2 = i; //j1(保留字、标识符、无符号整数)、j2(运算符)

            // 标记非法字符
            if (!((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || y[input[i]] == 1 || J[input[i]] == 1))
                illegalFlag = 1;

            // 识别数字与字母串
            while (input[j1] != '\0' && ((input[j1] >= '0' && input[j1] <= '9') || (input[j1] >= 'a' && input[j1] <= 'z') || (input[j1] >= 'A' && input[j1] <= 'Z'))) {
                if (input[j1] >= '0' && input[j1] <= '9') numFlag = 1; // 标记数字 
                else letterFlag = 1; // 标记字母 
                j1++;
            }

            // 识别运算符，并标记运算符 
            while (input[j2] != '\0' && y[input[j2]] == 1) {
                operatorFlag = 1;
                j2++;
            }

            // 识别界符，并标记界符
            if (J[input[i]] == 1)
                boundaryFlag = 1;

            //提取字符串
            if (numFlag || letterFlag)
                word = input.substr(i, j1 - i);


            //无符号整数
            if (numFlag == 1 && letterFlag == 0 && !f && !F) {
                if (word.size() <= 8) cout << "(无符号整数," << word << ")" << endl;
                else cout << "(无符号整数越界," << word << ",行号:" << line << ")" << endl;
                wordTable.push_back(word);
            }
            //标识符
            else if (letterFlag == 1 && B[word] != 1 && !f && !F) {
                if (input[i] >= '0' && input[i] <= '9') cout << "(非法字符(串)," << word << ",行号:" << line << ")" << endl; //识别非法字符串
                else if (word.size() <= 8) cout << "(标识符," << word << ")" << endl;
                else cout << "(标识符长度超长," << word << ",行号:" << line << ")" << endl;
                wordTable.push_back(word);
            }
            //保留字
            else if (letterFlag == 1 && B[word] == 1 && !f && !F) {
                cout << "(保留字," << word << ")" << endl;
                wordTable.push_back(word);
            }
            //运算符及注释
            else if (operatorFlag == 1) {
                word = input.substr(i, j2 - i); // 提取字符串
                if (word == s1) f = 1; // '//'注释,标记'//' 
                else if (word == s2) F = 1; // '/*'注释,标记'/*'
                else if (word == s3) F = 0; // '*/'注释,解除'/*/'标记
                else if (!f && !F) {
                    cout << "(运算符," << word << ")" << endl;
                    wordTable.push_back(word);
                }
            }
            //界符 
            else if (boundaryFlag == 1 && !f && !F) {
                word = input[i];
                cout << "(界符," << word << ")" << endl;
                wordTable.push_back(word);
            }
            //识别非法字符
            else if (illegalFlag == 1 && !f && !F) {
                cout << "(非法字符(串)," << input[i] << ",行号:" << line << ")" << endl;
                wordTable.push_back(word);
            }

            if (j1 != i)
                i = j1 - 1;
            else if (j2 != i)
                i = j2 - 1;
        }
    }
}

int ReadFile(string path) {
    infile.open(path.c_str());
    if (!infile.is_open()) {
        cout << "输入文件打开失败！" << endl;
        return 0;
    }
    return 1;
}

int WriteFile(string path) {
    outfile.open(path.c_str());
    if (!outfile.is_open()) {
        cout << "输出文件打开失败！" << endl;
        return 0;
    }
    else {
        for (int i = 0; i < wordTable.size(); i++) {
            outfile << wordTable[i] << endl;
        }
        return 1;
    }
}

int main() {
    // 要分析的 源程序串 的地址
    string source_path = "E:\\CodeStudy\\CodeStudy\\CompilationPrinciples\\source\\lexical_source_1.txt";
    // 要写入结果的 文件 的地址
    string result_path = "E:\\CodeStudy\\CodeStudy\\CompilationPrinciples\\result\\lexical_result.txt";
    if (ReadFile(source_path)) {
        LexicalAnalysis();
        if (WriteFile(result_path)) {
            cout << "\n单词表已保存到文件中" << endl;
        }
    }
    return 0;
}