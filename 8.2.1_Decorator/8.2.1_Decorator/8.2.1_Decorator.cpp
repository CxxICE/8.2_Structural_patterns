#include <iostream>
#include <string>
#include <algorithm>

class Text 
{
public:
	virtual void render(const std::string &data, const std::string &href = "") const
	{
		std::cout << data;
	}
};


class DecoratedText : public Text 
{
public:
	explicit DecoratedText(Text *text) : text_(text) {}
	Text *text_;
};

class ItalicText : public DecoratedText 
{
public:
	explicit ItalicText(Text *text) : DecoratedText(text) {}
	void render(const std::string &data, const std::string &href = "") const override
	{
		std::cout << "<i>";
		text_->render(data, href);
		std::cout << "</i>";
	}
};

class BoldText : public DecoratedText 
{
public:
	explicit BoldText(Text *text) : DecoratedText(text) {}
	void render(const std::string &data, const std::string &href = "") const override
	{
		std::cout << "<b>";
		text_->render(data, href);
		std::cout << "</b>";
	}
};

class Paragraph : public DecoratedText 
{
public:
	explicit Paragraph(Text *text) : DecoratedText(text) {}
	void render(const std::string &data, const std::string &href = "") const override
	{
		std::cout << "<p>";
		text_->render(data, href);
		std::cout << "</p>";
	}
};

class Reversed : public DecoratedText 
{
public:
	explicit Reversed(Text *text) : DecoratedText(text) {}
	void render(const std::string &data, const std::string &href = "") const override
	{
		std::string tmp = data;
		//auto it_r = tmp.rbegin();
		//for (auto it_f = tmp.begin(); it_f < it_r.base(); ++it_f, ++it_r)
		//{
		//	std::swap(*it_f, *it_r);
		//}
		std::reverse(tmp.begin(), tmp.end());
		text_->render(tmp, href);
	}
	
};

class Link : public DecoratedText 
{
public:
	explicit Link(Text *text) : DecoratedText(text) {}
	void render(const std::string &data, const std::string &href) const override
	{
		std::cout << "<a href=" << href << ">";
		text_->render(data, href);
		std::cout << "</a>";
	}
};

int main() 
{
	{
		std::cout << "\x1B[36m" << "ItalicText + BoldText" << "\x1B[0m" << std::endl;
		auto text_block = new ItalicText(new BoldText(new Text()));
		text_block->render("Hello world");
		std::cout << std::endl;
	}

	{
		std::cout << "\x1B[36m" << "Paragraph" << "\x1B[0m" << std::endl;
		auto text_block = new Paragraph(new Text());
		text_block->render("Hello world");
		std::cout << std::endl;
	}

	{
		std::cout << "\x1B[36m" << "Link" << "\x1B[0m" << std::endl;
		auto text_block = new Link(new Text());
		text_block->render("Hello world", "netology.ru");
		std::cout << std::endl;
	}

	{
		std::cout << "\x1B[36m" << "ItalicText + Link" << "\x1B[0m" << std::endl;
		auto text_block = new ItalicText(new Link(new Text()));
		text_block->render("Hello world", "netology.ru");
		std::cout << std::endl;
	}

	{
		std::cout << "\x1B[36m" << "Reversed" << "\x1B[0m" << std::endl;
		auto text_block = new Reversed(new Text());
		text_block->render("Hello world");
		std::cout << std::endl;
	}

	{
		std::cout << "\x1B[36m" << "BoldText + Reversed + ItalicText" << "\x1B[0m" << std::endl;
		auto text_block = new BoldText(new Reversed(new ItalicText(new Text())));
		text_block->render("Hello world");
		std::cout << std::endl;
	}
	
	{
		std::cout << "\x1B[36m" << "BoldText + Reversed + ItalicText + Link + Paragraph" << "\x1B[0m" << std::endl;
		auto text_block = new BoldText(new Reversed(new ItalicText(new Link(new Paragraph(new Text())))));
		text_block->render("Hello world", "netology.ru");
		std::cout << std::endl;
	}
}