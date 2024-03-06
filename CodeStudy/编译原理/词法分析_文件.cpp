#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

ifstream infile;    // �ļ�������
ofstream outfile;   // �ļ������

vector<string> wordTable;	// ���ʱ�
map<string, int> B;         // ������
map<string, int> Y;         // �����
map<char, int> J;           // ���
map<char, int> y;           // 
string s1 , s2, s3 ;
int F; // ���'/*''*/'ע��

void Init() {
    B["const"] = B["var"] = B["procedure"] = B["begin"] = B["end"] = B["odd"] = B["if"] = B["then"] = B["call"] = B["while"] = B["do"] = B["read"] = B["write"] = 1; //�����֣�13�� 
    Y["+"] = Y["-"] = Y["*"] = Y["/"] = Y["<"] = Y["<="] = Y[">"] = Y[">="] = Y["#"] = Y["="] = Y[":="] = 1; //�������11�� 
    y['+'] = y['-'] = y['*'] = y['/'] = y['<'] = y['>'] = y['='] = y['#'] = y[':'] = 1;
    J['('] = J[')'] = J[','] = J[';'] = J['.'] = 1; //�����5��
    s1 = "//", s2 = "/*", s3 = "*/";
}

void LexicalAnalysis() {
    string input, word;
    Init();
    for (int line = 1; getline(infile, input); line++) {
        int f = 0; // ���'//'ע��
        for (int i = 0; input[i] != '\0'; i++) {
            // ȥ���ո���'\t'
            while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
                i++;

            int numFlag = 0, letterFlag = 0, operatorFlag = 0, boundaryFlag = 0, illegalFlag = 0;
            int j1 = i, j2 = i; //j1(�����֡���ʶ�����޷�������)��j2(�����)

            // ��ǷǷ��ַ�
            if (!((input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || y[input[i]] == 1 || J[input[i]] == 1))
                illegalFlag = 1;

            // ʶ����������ĸ��
            while (input[j1] != '\0' && ((input[j1] >= '0' && input[j1] <= '9') || (input[j1] >= 'a' && input[j1] <= 'z') || (input[j1] >= 'A' && input[j1] <= 'Z'))) {
                if (input[j1] >= '0' && input[j1] <= '9') numFlag = 1; // ������� 
                else letterFlag = 1; // �����ĸ 
                j1++;
            }

            // ʶ������������������� 
            while (input[j2] != '\0' && y[input[j2]] == 1) {
                operatorFlag = 1;
                j2++;
            }

            // ʶ����������ǽ��
            if (J[input[i]] == 1)
                boundaryFlag = 1;

            //��ȡ�ַ���
            if (numFlag || letterFlag)
                word = input.substr(i, j1 - i);


            //�޷�������
            if (numFlag == 1 && letterFlag == 0 && !f && !F) {
                if (word.size() <= 8) cout << "(�޷�������," << word << ")" << endl;
                else cout << "(�޷�������Խ��," << word << ",�к�:" << line << ")" << endl;
                wordTable.push_back(word);
            }
            //��ʶ��
            else if (letterFlag == 1 && B[word] != 1 && !f && !F) {
                if (input[i] >= '0' && input[i] <= '9') cout << "(�Ƿ��ַ�(��)," << word << ",�к�:" << line << ")" << endl; //ʶ��Ƿ��ַ���
                else if (word.size() <= 8) cout << "(��ʶ��," << word << ")" << endl;
                else cout << "(��ʶ�����ȳ���," << word << ",�к�:" << line << ")" << endl;
                wordTable.push_back(word);
            }
            //������
            else if (letterFlag == 1 && B[word] == 1 && !f && !F) {
                cout << "(������," << word << ")" << endl;
                wordTable.push_back(word);
            }
            //�������ע��
            else if (operatorFlag == 1) {
                word = input.substr(i, j2 - i); // ��ȡ�ַ���
                if (word == s1) f = 1; // '//'ע��,���'//' 
                else if (word == s2) F = 1; // '/*'ע��,���'/*'
                else if (word == s3) F = 0; // '*/'ע��,���'/*/'���
                else if (!f && !F) {
                    cout << "(�����," << word << ")" << endl;
                    wordTable.push_back(word);
                }
            }
            //��� 
            else if (boundaryFlag == 1 && !f && !F) {
                word = input[i];
                cout << "(���," << word << ")" << endl;
                wordTable.push_back(word);
            }
            //ʶ��Ƿ��ַ�
            else if (illegalFlag == 1 && !f && !F) {
                cout << "(�Ƿ��ַ�(��)," << input[i] << ",�к�:" << line << ")" << endl;
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
        cout << "�����ļ���ʧ�ܣ�" << endl;
        return 0;
    }
    return 1;
}

int WriteFile(string path) {
    outfile.open(path.c_str());
    if (!outfile.is_open()) {
        cout << "����ļ���ʧ�ܣ�" << endl;
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
    // Ҫ������ Դ���� �ĵ�ַ
    string source_path = "E:\\CodeStudy\\CodeStudy\\CompilationPrinciples\\source\\lexical_source_1.txt";
    // Ҫд������ �ļ� �ĵ�ַ
    string result_path = "E:\\CodeStudy\\CodeStudy\\CompilationPrinciples\\result\\lexical_result.txt";
    if (ReadFile(source_path)) {
        LexicalAnalysis();
        if (WriteFile(result_path)) {
            cout << "\n���ʱ��ѱ��浽�ļ���" << endl;
        }
    }
    return 0;
}