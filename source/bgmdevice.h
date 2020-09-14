#ifndef BGMDEVICE_H
#define BGMDEVICE_H

class BgmDevice
{
public:
    virtual void process() = 0;
    virtual bool needs_processing() = 0;

};

#endif // BGMDEVICE_H
