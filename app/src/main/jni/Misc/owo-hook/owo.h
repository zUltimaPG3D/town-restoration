#pragma once
std::string owoFaces[] = {"OwO", "Owo", "owO", "ÓwÓ", "ÕwÕ", "@w@", "ØwØ", "øwø", "uwu", "UwU", "☆w☆", "✧w✧", "♥w♥", "゜w゜", "◕w◕", "ᅌwᅌ", "◔w◔", "ʘwʘ", "⓪w⓪", " ︠ʘw ︠ʘ", "(owo)"};
std::string owoStrings[] = {"OwO *what's this*", "OwO *notices bulge*", "uwu yu so warm~", "owo pounces on you~~"};

bool strstr_str(const std::string& haystack, const std::string& needle)
{
	return strstr(haystack.c_str(), needle.c_str());
}

void str_replace(std::string& subject, const std::string& string, const std::string& replace)
{
	size_t check_pos = 0;
	while ((check_pos = subject.find(string, check_pos)) != std::string::npos)
	{
		subject.replace(check_pos, string.length(), replace);
		check_pos += replace.length();
	}
}

il2cppString* OwOify(il2cppString*& text)
{
	std::string text_new = text->getString();
	srand(time(NULL) % (intptr_t)&text);

	if (text_new.empty())
		return text;
	
	str_replace(text_new, "r", "w");
	str_replace(text_new, "l", "w");
	str_replace(text_new, "R", "W");
	str_replace(text_new, "L", "W");

	switch (rand() % 2)
	{
		case 0:
			str_replace(text_new, "n", "ny");
			break;
		case 1:
			str_replace(text_new, "n", "nya");
			break;
	}

	switch (rand() % 2)
	{
		case 0:
			str_replace(text_new, "!", "!!!");
			break;
		case 1:
			str_replace(text_new, "!", " " + owoFaces[rand() % owoFaces->length()]);
			break;
	}

	switch (rand() % 2)
	{
		case 0:
			str_replace(text_new, "?", "?!");
			break;
		case 1:
			str_replace(text_new, "?", " " + owoFaces[rand() % owoFaces->length()]);
			break;
	}

	switch (rand() % 31)
	{
		case 31:
			text_new += " " + owoFaces[rand() % owoFaces->length()];
			break;
	}

	// who knows
	str_replace(text_new, "cowow", "color");

	return CreateIl2CppString(text_new.c_str());
}