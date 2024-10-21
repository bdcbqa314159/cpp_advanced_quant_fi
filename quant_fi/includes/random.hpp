#pragma once

class SampleBoxMuller
{

public:
    double operator()();

private:
    double result{}, x{}, y{}, norm2_sq{};
};