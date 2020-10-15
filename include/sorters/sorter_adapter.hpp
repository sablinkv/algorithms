#pragma once
#include "sorter_policy.hpp"

namespace algorithms {
    template<class Sorter, template<typename> class Interface_policy = policy::full_interface>
    class sort_adapter : 
        public Sorter, 
        public Interface_policy<sort_adapter<Sorter, Interface_policy>>
    {
    public:
        using sorter_type = Sorter;
        using interface_type = Interface_policy<sort_adapter<Sorter, Interface_policy>>;
        
        sort_adapter(sorter_type&& impl = {}, interface_type&& interface = {})
            : sorter_type(std::move(impl)), interface_type(std::move(interface))
        {}

    private:
        friend interface_type;
    };
} // namespace algorithms
