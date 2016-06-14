/*
 * 파일 : fileIO.h
 * 내용 : 파일 입출력 선언
 * 제작 : 박강민
 */

#pragma once
#ifndef _FILE_IO_H
#define _FILE_IO_H

static const char *fileName = "data.dat";

// 게임 저장 함수
bool SaveGame();

// 게임 불러오기 함수
bool LoadGame();

#endif