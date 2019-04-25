#pragma once

#include "file.hpp"

#include <sstream>
#include <iostream>


class Diff {
    public:
        Diff(const File & firstFile, const File & secondFile);
        Diff(const Diff & src);
        virtual ~Diff();
        
        virtual bool Compare() = 0;

        Diff & operator=(const Diff & src);
        friend std::ostream & operator<<(std::ostream & os, const Diff & src);

    protected:
        File * _first;
        File * _second;
};

class BinDiff : public Diff {
    public:
        BinDiff(const File & firstFile, const File & secondFile);
        BinDiff(const BinDiff & src);
        virtual ~BinDiff();
        
        virtual bool Compare() override;

        friend std::ostream & operator<<(std::ostream & os, const BinDiff & src);
};

class TxtDiff : public Diff {
    public:
        TxtDiff(const File & firstFile, const File & secondFile);
        TxtDiff(const TxtDiff & src);
        virtual ~TxtDiff();
        
        virtual bool Compare() override;

        friend std::ostream & operator<<(std::ostream & os, const TxtDiff & src);
};

class JsnDiff : public Diff {
    public:
        JsnDiff(const File & firstFile, const File & secondFile);
        JsnDiff(const JsnDiff & src);
        virtual ~JsnDiff();
        
        virtual bool Compare();

        friend std::ostream & operator<<(std::ostream & os, const JsnDiff & src);
};
