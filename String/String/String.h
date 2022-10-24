#pragma once

class String
{
public:
	String(const char* s) : string(s) {}
	~String() {}
	String(const String& s) : string(s.string) {}
	String(String&& s) : string(s.string) {
		s.string = nullptr;
	}

private:
	const char* string;
};

