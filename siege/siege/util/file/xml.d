/**
 * Copyright:  (c) 2005-2008 Eric Poggel
 * Authors:    Andy Friesen, Eric Poggel
 * License:    <a href="lgpl.txt">LGPL</a>
 *
 * Xml contains functions and classes for reading, parsing, and writing xml
 * documents.
 *
 * This hasn't been profiled and probably isn't that efficient.  Perhaps it should
 * eventually be switched to Tango's or Phobos's xml libraries.
 *
 * History:
 * Most of the code in this module originally came from Andy Friesen's Xmld.
 * Xmld was unmaintained, but Andy had placed it in the public domain.  This
 * version has been modified to compile under recent versions of dmd and
 * consolidated into a single module.
 */

module siege.util.file.xml;

/*
    Begin parse.d
*/
/// Encode characters such as &, <, >, etc. as their xml/html equivalents
char[] xmlEncode(char[] src)
{   char[] tempStr;
	tempStr = replace(src    , "&", "&amp;");
	tempStr = replace(tempStr, "<", "&lt;");
	tempStr = replace(tempStr, ">", "&gt;");
	return tempStr;
}

/// Convert xml-encoded special characters such as &amp;amp; back to &amp;.
char[] xmlDecode(char[] src)
{	char[] tempStr;
	tempStr = replace(src    , "&amp;", "&");
	tempStr = replace(tempStr, "&lt;",  "<");
	tempStr = replace(tempStr, "&gt;",  ">");
	return tempStr;
}
/*
    End parse.d
*/

private
{
    import std.stream;
    import std.string;
    import std.regexp;
    import std.stdio;
}

/**
 * Read an entire stream into a tree of XmlNodes.
 * Example:
 * --------------------------------
 * XmlNode xml;
 * File file = new File(source, FileMode.In);
 * xml = readDocument(file);
 * file.close();
 * --------------------------------*/
XmlNode readDocument(Stream src)
{
	XmlStream stream = new XmlStream(src);
	char[] tok = stream.readNode();

	// TODO: actually do something with the DOCTYPE?
	if (tok.length >= 9 && tolower(tok[0..9]) == "<!doctype")
		tok = stream.readNode();
	if (tok.length >= 6 && tolower(tok[0..6]) == "<? xml")
		tok = stream.readNode();
	if (tok.length >= 5 && tolower(tok[0..5]) == "<?xml")
		tok = stream.readNode();

	XmlNode node = XmlNode.parseNode(null, tok, stream);
	delete stream;
	return node;
}

XmlNode readDocument(char[] filename)
{	File file = new File(filename, FileMode.In);
	XmlNode xml = readDocument(file);
	file.close();
	return xml;
}

/// An exception thrown on an xml parsing error.
class XmlError : Exception
{	/// Throws an exception with the current line number and an error message.
	this(uint lineNumber, char[] msg)
	{	super("(Line " ~ .toString(lineNumber) ~ ")" ~ msg);
	}
}

/**
 * XmlNode represents a single xml node and has methods for modifying
 * attributes and adding children.  All methods that make changes modify this
 * XmlNode rather than making a copy, unless otherwise noted.  Many methods
 * return a self reference to allow cascaded calls.
 * Example:
 * --------------------------------
 * // Create an XmlNode tree with attributes and cdata, and write it to a file.
 * node.addChild(new XmlNode("mynode").setAttribute("x", 50).
 *     addChild(new XmlNode("Waldo").addCdata("Hello!"))).write("myfile.xml");
 * --------------------------------*/
class XmlNode
{
    protected char[] _name;
    protected char[][char[]] _attributes;
    protected XmlNode[]      _children;
    protected static RegExp  _attribRe;
    protected static RegExp  _attribSplitRe;
    protected static RegExp trim_trailing_quote;

    /// A specialialized XmlNode for CData.
	class CData : XmlNode
	{
		private char[] _cdata;

		this(char[] cdata)
		{	_cdata = xmlDecode(cdata);
		}

		bool isCData()
		{	return true;
		}

		char[] getCData()
		{	return _cdata;
		}

		protected override void write(Stream dest, int indentLevel)
		{	char[] pad = new char[indentLevel];
			pad[] = ' ';
			dest.writeString(pad);
			dest.writeLine(xmlEncode(_cdata));
		}
	}

	static this()
	{	// disallowed attribute values are "<>%
		_attribRe = new RegExp("([a-z0-9]+)\\s*=\\s*\"([^\"^<^>^%]+)\"\\s*", "gim");
		_attribSplitRe = new RegExp("\\s*=\\s*\"", ""); // splits so an
		trim_trailing_quote = new RegExp("\"\\s*");
	}

	/// Construct an empty XmlNode.
	this()
	{}

	/// Construct and set the name of this XmlNode to name.
	this(char[] name)
	{	_name = name;
	}

	/// Get the name of this XmlNode.
	char[] getName()
	{	return _name;
	}

	/// Set the name of this XmlNode.
	void setName(char[] newName)
	{	_name = newName;
	}

	/// Does this XmlNode have an attribute with name?
	bool hasAttribute(char[] name)
	{	return (name in _attributes) !is null;
	}

	/// Get the attribute with name, or return null if no attribute has that name.
	char[] getAttribute(char[] name)
	{	if (name in _attributes)
			return _attributes[name];
		else
			return null;
	}

	/// Return an array of all attributes (by reference, no copy is made).
	char[][char[]] getAttributes()
	{	return _attributes;
	}

	/**
	 * Set an attribute to a string value.  The attribute is created if it
	 * doesn't exist.*/
	XmlNode setAttribute(char[] name, char[] value)
	{	_attributes[name] = value;
		return this;
	}

	/**
	 * Set an attribute to an integer value (stored internally as a string).
	 * The attribute is created if it doesn't exist.*/
	XmlNode setAttribute(char[] name, int value)
	{	return setAttribute(name, std.string.toString(value));
	}

	/**
	 * Set an attribute to a flaot value (stored internally as a string).
	 * The attribute is created if it doesn't exist.*/
	XmlNode setAttribute(char[] name, float value)
	{	return setAttribute(name, std.string.toString(value));
	}

	/// Remove the attribute with name.
	XmlNode removeAttribute(char[] name)
	{	_attributes.remove(name);
		return this;
	}

	/// Add an XmlNode child.
	XmlNode addChild(XmlNode newNode)
	{	_children ~= newNode;
		return this;
	}

	/// Return an array of all child XmlNodes.
	XmlNode[] getChildren()
	{	return _children;
	}

	/// Add a child Node of cdata (text).
	XmlNode addCdata(char[] cdata)
	{	addChild(new CData(cdata));
		return this;
	}

	/// Read this XmlNode from a file with filename.
	void read(char[] filename)
	{	File file = new File(filename, FileMode.In);
		read(file);
		file.close();
	}

	/// Read this XmlNode from a Stream.
	void read(Stream src)
	{	XmlStream xmlstream = new XmlStream(src);
		read(xmlstream);
		delete xmlstream;
	}

	/// Write this XmlNode to a file with filename.
	void write(char[] filename)
	{	File file = new File(filename, FileMode.Out);
		write(file);
		file.close();
	}

	/// Write this XmlNode and all children to a Stream.
	void write(Stream dest)
	{	write(dest, 0);
	}

	protected char[] asOpenTag()
	{	char[] s = "<" ~ _name;

		if (_attributes.length > 0)
		{	char[][] k = _attributes.keys;
			char[][] v = _attributes.values;
			for (int i = 0; i < _attributes.length; i++)
				s ~= " " ~ k[i] ~ "=\"" ~ v[i] ~ "\"";
		}

		if (_children.length == 0)
			s ~= " /"; // We want <blah /> if the node has no children.
		s ~= ">";

		return s;
	}

	protected char[] asCloseTag()
	{	if (_children.length != 0)
			return "</" ~ _name ~ ">";
		else
			return ""; // don't need it.  Leaves close themselves via the <blah /> syntax.
	}

	protected bool isCdata()
	{	return false;
	}

	protected bool isLeaf()
	{	return _children.length == 0;
	}

	protected void write(Stream dest, int indentLevel)
	{
		char[] pad = new char[indentLevel];
		pad[] = ' ';
		dest.writeString(pad);
		dest.writeLine(asOpenTag());

		if (_children.length)
		{
			for (int i = 0; i < _children.length; i++)
			{
				_children[i].write(dest, indentLevel + 4); // TODO: make the indentation level configurable.
			}
			dest.writeString(pad);
			dest.writeLine(asCloseTag());
		}
	}

	protected static XmlNode parseNode(XmlNode parent, char[] tok, XmlStream src)
	{
		// Local functions
		char[][] parseAttributes(char[] tag)
		{	char[][] result;

			int pos = std.string.find(tag, cast(char)' ');
			if (pos == -1) return result;

			char[][] matches = _attribRe.match(tag[pos..tag.length]);
			for (int i = 0; i < matches.length; i++)
			{	// cheap hack (modified by Eric Poggel to support attribute values with spaces).
				char[][] blah = _attribSplitRe.split(matches[i]);
				result ~= blah[0];									// attribute name
				result ~= trim_trailing_quote.replace(blah[1], "");	// attribute value
			}
			return result;
		}

		XmlNode newNode = null;

		int pos = 2;
		while (pos < tok.length && tok[pos] != ' ' && tok[pos] != '/' && tok[pos] != '>')
			pos++;   // stop at a space, a slash, or the end bracket.

		if (std.string.find(letters, tok[1]) != -1)
		{	newNode = new XmlNode(tok[1 .. pos]); // new node
			if (parent !is null)
				parent.addChild(newNode);

			// parse attributes
			char[][] attribs = parseAttributes(tok);

			for (int i = 0; i < attribs.length; i += 2)
				newNode.setAttribute(attribs[i], attribs[i + 1]);

			if (tok[tok.length - 2] != '/')     // matched tag
				newNode.read(src);
		}
		else
			// Invalid tag name
			throw new XmlError(src.lineNumber(), "Tags cannot start with " ~ tok);

		return newNode;
	}

	protected void read(XmlStream src)
	{	while (true)
		{	char[] tok = src.readNode();

			if (tok[0] == '<')
			{	if (tok[1] != '/')
					parseNode(this, tok, src);
				else
				{	if (tok[2 .. _name.length + 2] != _name)
						throw new XmlError(src.lineNumber(), "</" ~ _name ~ "> or opening tag expected.  Got " ~ tok);
					else
						break;
				}
			}
			else
				addCdata(std.string.strip(tok));
		}
	}
}


/**
 * Helper Class for XmlNode
 * Authors: Andy Friesen */
private class XmlStream
{
    private Stream _stream;
    private int _curLine;

	this(Stream s)
	{	_stream = s;
		_curLine = 0;
	}

	char getc()
	{	char c = _stream.getc();
		if (c == '\n') _curLine++;
		return c;
	}

	void ungetc(char c)
	{	if (c == '\n') _curLine--;
		_stream.ungetc(c);
	}

	char[] readString(uint count)
	{	char[] result = new char[count];
		int i;
		try
		{	for (i=0; i < count; i++)
				result[i] = getc();
			return result;
		}catch
		{	return result[0 .. i];
		}
	}

	void unReadString(char[] str)
	{	for (int i=str.length-1; i>=0; i--)
			ungetc(str[i]);
	}

	void eatWhiteSpace()
	{	char ch = getc();
		while (std.string.find(whitespace, ch) != -1)
			ch = getc();
		ungetc(ch);

		// Now to eat comments. (may as well make it as transparent as possible)
		char[] str = readString(4);
		if (str == "<!--")
		{	char[] last = "   ";
			do
			{	char c = getc();
				last = last[1..3];
				last ~= c;
				if (_stream.eof())
					throw new XmlError(lineNumber(), "Unexpected end of file while parsing comment.");
			} while (last != "-->");
			eatWhiteSpace();
		}
		else
			unReadString(str);
	}

	private char[] getToken()
	{
		// A helper function
		bool isTokenChar(char c)
		{   static const char[] tokenChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
			return std.string.find(tokenChars, c) != -1;
		}

		char[] token;
		try
		{	eatWhiteSpace();
			char ch = getc();
			if (isTokenChar(ch))
			{	while (isTokenChar(ch)) // grab all alphanumeric characters until we hit nonalphanumeric
				{	token ~= ch;
					ch = getc();
				}
				ungetc(ch);
			}
			else
				token ~= ch;

			return token;
		}catch
		{	throw new XmlError(lineNumber(), "Unexpected end of file");
		}
	}

	void expect(char[] tok)
	{	eatWhiteSpace();
		char[] s;
		for (int i = 0; i < tok.length; i++)
		{	char ch = getc();
			s ~= ch;
			if (ch != tok[i])
				throw new XmlError(lineNumber(), "Expected: \"" ~ tok ~ "\".  Got: \"" ~ s ~ "\"");
		}
	}

	char[] readUntil(char end)
	{	char[] s;
		char ch = getc();
		while (ch != end)
		{	s ~= ch;
			ch = getc();
			if (_stream.eof())
				throw new XmlError(lineNumber(), "Unexpected end of file");
		}
		ungetc(ch); // put it back
		return s;
	}

	char[] readNode()
	{	eatWhiteSpace();
		char ch = getc();

		if (ch == '<')                                 // data node
		{	char[] nodeName = getToken();
			if (nodeName == "/")                        // closing tag
			{	nodeName = getToken();
				expect(">");
				return "</" ~ nodeName ~ ">";
			}
			else
			{	char[] attribs = strip(readUntil('>'));
				expect(">");
				return "<" ~ nodeName ~ " " ~ attribs ~ ">";
		}	}
		else  // cdata
		{	ungetc(ch);
			return readUntil('<');
		}
	}

	int lineNumber()
	{	return _curLine;
	}
}
