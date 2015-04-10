/*
 * BlaPDBResult.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Chao
 */

#ifndef BLAPDBRESULT_H_
#define BLAPDBRESULT_H_
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
class BlaPDBResult {
public:
	BlaPDBResult();
	virtual ~BlaPDBResult();
	string& getAlignment();
	void setAlignment(string& alignment);
	float getExpect();
	void setExpect(float expect);
	bool isFirstStateReached();
	void setFirstStateReached(bool);
	int getGaps();
	void setGaps(int gaps);
	int getIdentities();
	void setIdentities(int identities);
	int getLength();
	void setLength(int length);
	int getPositives();
	void setPositives(int positives);
	string& getProteinName();
	void setProteinName(string& proteinName);
	string& getQuery();
	void setQuery(string& query);
	int getQueryEnd();
	void setQueryEnd(int queryEnd);
	int getQueryStart();
	void setQueryStart(int queryStart);
	float getScore();
	void setScore(float score);
	bool isSecondStateReached();
	void setSecondStateReached(bool);
	string& getSubject();
	void setSubject(string& subject);
	int getSubjectEnd();
	void setSubjectEnd(int subjectEnd);
	int getSubjectStart();
	void setSubjectStart(int subjectStart);
	bool isThirdStateReached();
	void setThirdStateReached(bool);

private:
	//the first state
	//if next line contains">", we should read the
	//protein name and the next item is length
	string proteinName;
	int length;
	bool firstStateReached;

	//the second state contains score, expect, identities,
	//positives, and gaps
	float score;
	float expect;
	int identities;
	int positives;
	int gaps;
	bool secondStateReached;

	//the third state is query ,alignment and subject
	int queryStart;
	string query;
	int queryEnd;
	string alignment;
	int subjectStart;
	string subject;
	int subjectEnd;
	bool thirdStateReached;
};

#endif /* BLAPDBRESULT_H_ */
