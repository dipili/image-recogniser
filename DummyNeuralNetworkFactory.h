#pragma once

namespace irec
{
    class NeuralNetwork;

    class DummyNeuralNetworkFactory
    {
    public:
        DummyNeuralNetworkFactory();

        NeuralNetwork* createInstance() const;
    };
}
