//============================================================================
// Name        : testParser.cpp
// Author      : Chao Fang
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "BlaPDBResult.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	FILE* fptr = fopen(argv[1], "r");
	ofstream outputFile(argv[2]);
	char line[500];
	int counter = 1;
	BlaPDBResult result;
	outputFile << "{\n";
	while (fgets(line, 500, fptr) != NULL) {
		if ((strstr(line, ">") != NULL) && !result.isFirstStateReached()) {
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//set first state reached
			result.setFirstStateReached(true);
		}
		if ((strstr(line, "Score =") != NULL)
				&& !result.isSecondStateReached()) {
			//set second block information
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);
			char* pos3 = strstr(pos2 + 1, "(");
			if (pos3 == NULL) {
				//there is no gaps
				result.setGaps(0);
			} else {
				int gaps;
				sscanf(pos3 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			//set second state reached
			result.setSecondStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && !result.isThirdStateReached()) {
			//set third block information
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			result.setQueryStart(nInt1);
			string tmpQueryStr(tmpQuery);
			result.setQuery(tmpQueryStr);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string tmpLineStr(line);
			result.setAlignment(tmpLineStr);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			result.setSubjectStart(nInt1);
			string tmpSubjectStr(tmpSubject);
			result.setSubject(tmpSubjectStr);
			result.setSubjectEnd(nInt2);
			//set third state reached
			result.setThirdStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && result.isThirdStateReached()) {
			//update third block information, so in this case
			//query, alignment and subject should be long string
			//the queryEnd and subjectEnd should also be updated
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			string newQuery = result.getQuery();
			newQuery += tmpQuery;
			result.setQuery(newQuery);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string newAlignment = result.getAlignment();
			newAlignment += line;
			result.setAlignment(newAlignment);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			string newSubject = result.getSubject();
			newSubject += tmpSubject;
			result.setSubject(newSubject);
			result.setSubjectEnd(nInt2);

		}

		if ((strstr(line, "Score =") != NULL)
				&& result.isSecondStateReached()) {

			//first write the protein information to json
			outputFile << "\"protein" << counter << "\":{\n";
			outputFile << "\t\"proteinName\":\"" << result.getProteinName()
					<< "\",\n";
			outputFile << "\t\"Length\":\"" << result.getLength() << "\",\n";
			outputFile << "\t\"Score\":\"" << result.getScore() << "\",\n";
			outputFile << "\t\"Expect\":\"" << result.getExpect() << "\",\n";
			outputFile << "\t\"Identities\":\"" << result.getIdentities()
					<< "\",\n";
			outputFile << "\t\"Positives\":\"" << result.getPositives()
					<< "\",\n";
			outputFile << "\t\"Gaps\":\"" << result.getGaps() << "\",\n";
			outputFile << "\t\"QueyStart\":\"" << result.getQueryStart()
					<< "\",\n";
			outputFile << "\t\"Query\":\"" << result.getQuery() << "\",\n";
			outputFile << "\t\"QueryEnd\":\"" << result.getQueryEnd()
					<< "\",\n";
			outputFile << "\t\"Alignment\":\"" << result.getAlignment()
					<< "\",\n";
			outputFile << "\t\"SubjectStart\":\"" << result.getSubjectStart()
					<< "\",\n";
			outputFile << "\t\"Subject\":\"" << result.getSubject() << "\",\n";
			outputFile << "\t\"SubjectEnd\":\"" << result.getSubjectEnd()
					<< "\"\n";
			outputFile << "},\n";
			counter++;
			//then update the information and set the second state flag
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);
			char* pos3 = strstr(pos2 + 1, "(");
			if (pos3 == NULL) {
				//there is no gaps
				result.setGaps(0);
			} else {
				int gaps;
				sscanf(pos3 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			result.setSecondStateReached(true);
			//unset the third block flag
			result.setThirdStateReached(false);

		}
		if ((strstr(line, ">") != NULL) && result.isFirstStateReached()) {

			//first write the protein information to json
			outputFile << "\"protein" << counter << "\":{\n";
			outputFile << "\t\"proteinName\":\"" << result.getProteinName()
					<< "\",\n";
			outputFile << "\t\"Length\":\"" << result.getLength() << "\",\n";
			outputFile << "\t\"Score\":\"" << result.getScore() << "\",\n";
			outputFile << "\t\"Expect\":\"" << result.getExpect() << "\",\n";
			outputFile << "\t\"Identities\":\"" << result.getIdentities()
					<< "\",\n";
			outputFile << "\t\"Positives\":\"" << result.getPositives()
					<< "\",\n";
			outputFile << "\t\"Gaps\":\"" << result.getGaps() << "\",\n";
			outputFile << "\t\"QueyStart\":\"" << result.getQueryStart()
					<< "\",\n";
			outputFile << "\t\"Query\":\"" << result.getQuery() << "\",\n";
			outputFile << "\t\"QueryEnd\":\"" << result.getQueryEnd()
					<< "\",\n";
			outputFile << "\t\"Alignment\":\"" << result.getAlignment()
					<< "\",\n";
			outputFile << "\t\"SubjectStart\":\"" << result.getSubjectStart()
					<< "\",\n";
			outputFile << "\t\"Subject\":\"" << result.getSubject() << "\",\n";
			outputFile << "\t\"SubjectEnd\":\"" << result.getSubjectEnd()
					<< "\"\n";
			outputFile << "},\n";
			counter++;
			//then update the information set the first state flag
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//unset second block flag and third block flag
			result.setSecondStateReached(false);
			result.setThirdStateReached(false);
		}

	}

	//this case will print out the last protein
	outputFile << "\"protein" << counter << "\":{\n";
	outputFile << "\t\"proteinName\":\"" << result.getProteinName() << "\",\n";
	outputFile << "\t\"Length\":\"" << result.getLength() << "\",\n";
	outputFile << "\t\"Score\":\"" << result.getScore() << "\",\n";
	outputFile << "\t\"Expect\":\"" << result.getExpect() << "\",\n";
	outputFile << "\t\"Identities\":\"" << result.getIdentities() << "\",\n";
	outputFile << "\t\"Positives\":\"" << result.getPositives() << "\",\n";
	outputFile << "\t\"Gaps\":\"" << result.getGaps() << "\",\n";
	outputFile << "\t\"QueyStart\":\"" << result.getQueryStart() << "\",\n";
	outputFile << "\t\"Query\":\"" << result.getQuery() << "\",\n";
	outputFile << "\t\"QueryEnd\":\"" << result.getQueryEnd() << "\",\n";
	outputFile << "\t\"Alignment\":\"" << result.getAlignment() << "\",\n";
	outputFile << "\t\"SubjectStart\":\"" << result.getSubjectStart()
			<< "\",\n";
	outputFile << "\t\"Subject\":\"" << result.getSubject() << "\",\n";
	outputFile << "\t\"SubjectEnd\":\"" << result.getSubjectEnd() << "\"\n";
	outputFile << "},\n";

	//print the finishing line
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";
	fclose(fptr);
	outputFile.close();
	return 0;
}

