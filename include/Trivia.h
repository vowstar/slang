#pragma once

#include <cstdint>

#include "ArrayRef.h"
#include "Buffer.h"
#include "StringRef.h"

namespace slang {

class Token;
class SyntaxNode;

enum class TriviaKind : uint8_t {
    Unknown,
    Whitespace,
    EndOfLine,
    LineContinuation,
    LineComment,
    BlockComment,
    DisabledText,
    SkippedTokens,
    SkippedSyntax,
    Directive
};

class Trivia {
public:
    TriviaKind kind;

    Trivia() : kind(TriviaKind::Unknown), rawText(nullptr) {}
    Trivia(TriviaKind kind, StringRef rawText) : kind(kind), rawText(rawText) {}
    Trivia(TriviaKind kind, ArrayRef<Token> tokens) : kind(kind), tokens(tokens) {}
    Trivia(TriviaKind kind, SyntaxNode* syntax) : kind(kind), syntaxNode(syntax) {}

    void writeTo(Buffer<char>& buffer, uint8_t flags = 0) const;

    // data accessors for specific kinds of trivia
    // these will assert if the kind is wrong
    SyntaxNode* syntax() const;

private:
    union {
        StringRef rawText;
        ArrayRef<Token> tokens;
        SyntaxNode* syntaxNode;
    };
};

}