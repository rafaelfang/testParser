/*
 * BlaPDBResult.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Chao
 */

#include "BlaPDBResult.h"

BlaPDBResult::BlaPDBResult() {
	// TODO Auto-generated ructor stub

}

BlaPDBResult::~BlaPDBResult() {
	// TODO Auto-generated destructor stub
}

string& BlaPDBResult::getAlignment() {
	return alignment;
}

void BlaPDBResult::setAlignment(string& alignment) {
	this->alignment = alignment;
}

float BlaPDBResult::getExpect() {
	return expect;
}

void BlaPDBResult::setExpect(float expect) {
	this->expect = expect;
}

bool BlaPDBResult::isFirstStateReached() {
	return firstStateReached;
}

void BlaPDBResult::setFirstStateReached(bool firstStateReached = false) {
	this->firstStateReached = firstStateReached;
}

int BlaPDBResult::getGaps() {
	return gaps;
}

void BlaPDBResult::setGaps(int gaps) {
	this->gaps = gaps;
}

int BlaPDBResult::getIdentities() {
	return identities;
}

void BlaPDBResult::setIdentities(int identities) {
	this->identities = identities;
}

int BlaPDBResult::getLength() {
	return length;
}

void BlaPDBResult::setLength(int length) {
	this->length = length;
}

int BlaPDBResult::getPositives() {
	return positives;
}

void BlaPDBResult::setPositives(int positives) {
	this->positives = positives;
}

string& BlaPDBResult::getProteinName() {
	return proteinName;
}

void BlaPDBResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}

string& BlaPDBResult::getQuery() {
	return query;
}

void BlaPDBResult::setQuery(string& query) {
	this->query = query;
}

int BlaPDBResult::getQueryEnd() {
	return queryEnd;
}

void BlaPDBResult::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

int BlaPDBResult::getQueryStart() {
	return queryStart;
}

void BlaPDBResult::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

float BlaPDBResult::getScore() {
	return score;
}

void BlaPDBResult::setScore(float score) {
	this->score = score;
}

bool BlaPDBResult::isSecondStateReached() {
	return secondStateReached;
}

void BlaPDBResult::setSecondStateReached(bool secondStateReached = false) {
	this->secondStateReached = secondStateReached;
}

string& BlaPDBResult::getSubject() {
	return subject;
}

void BlaPDBResult::setSubject(string& subject) {
	this->subject = subject;
}

int BlaPDBResult::getSubjectEnd() {
	return subjectEnd;
}

void BlaPDBResult::setSubjectEnd(int subjectEnd) {
	this->subjectEnd = subjectEnd;
}

int BlaPDBResult::getSubjectStart() {
	return subjectStart;
}

void BlaPDBResult::setSubjectStart(int subjectStart) {
	this->subjectStart = subjectStart;
}

bool BlaPDBResult::isThirdStateReached() {
	return thirdStateReached;
}

void BlaPDBResult::setThirdStateReached(bool thirdStateReached = false) {
	this->thirdStateReached = thirdStateReached;
}
