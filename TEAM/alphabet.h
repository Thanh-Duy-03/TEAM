#pragma once
#include "Win.h"

class Alphabet
{
public:
	wstring A = L"▄▀█\n█▀█";
	wstring B = L"█▄▄\n█▄█";
	wstring C = L"█▀▀\n█▄▄";
	wstring D = L"█▀▄\n█▄▀";
	wstring E = L"█▀▀\n██▄";
	wstring F = L"█▀▀\n█▀ ";
	wstring G = L"█▀▀\n█▄█";
	wstring H = L"█ █\n█▀█";
	wstring I = L"█\n█";
	wstring J = L"  █\n█▄█";
	wstring K = L"█▄▀\n█ █";
	wstring L = L"█  \n█▄▄";
	wstring M = L"█▀▄▀█\n█ ▀ █";
	wstring N = L"█▄ █\n█ ▀█";
	wstring O = L"█▀█\n█▄█";
	wstring P = L"█▀█\n█▀▀";
	wstring Q = L"█▀█\n▀▀█";
	wstring R = L"█▀█\n█▀▄";
	wstring S = L"█▀\n▄█";
	wstring T = L"▀█▀\n █ ";
	wstring U = L"█ █\n█▄█";
	wstring V = L"█ █\n▀▄▀";
	wstring W = L"█ █ █\n▀▄▀▄▀";
	wstring X = L"▀▄▀\n█ █";
	wstring Y = L"█▄█\n █ ";
	wstring Z = L"▀█\n█▄";
	wstring alphabet[26] = { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
	int SizeAlphabet[26] = { 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 6, 5, 4, 4, 4, 4, 3, 4, 4, 4, 6, 4, 4, 3 };

	wstring Number0 = L"█▀█\n█▄█";
	wstring Number1 = L"▄█\n █";
	wstring Number2 = L"▀█\n█▄";
	wstring Number3 = L"▀▀█\n▄██";
	wstring Number4 = L"█ █\n▀▀█";
	wstring Number5 = L"█▀\n▄█";
	wstring Number6 = L"█▄▄\n█▄█";
	wstring Number7 = L"▀▀█\n  █";
	wstring Number8 = L"█▀█\n█▀█";
	wstring Number9 = L"█▀█\n▀▀█";
	wstring Numbers[10] = { Number0, Number1, Number2, Number3, Number4, Number5, Number6, Number7, Number8, Number9 };
	int SizeNumbers[10] = { 4, 3, 3, 4, 4, 3, 4, 4, 4, 4 };
};

