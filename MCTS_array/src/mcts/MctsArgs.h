/**
 * \file Mcts.h
 * \brief Define class Mcts
 * \author Benoit Viguier
 * \version 1.0
 * \date December 26th 2014
 *
 */
#pragma once
#include "../tools/typedef.h"
#include "../tools/Memory.h"

#if defined(DOUBLE_TREE)
	#define DIVIDE 2 * sizeof(Node)
#else
	#define DIVIDE (sizeof(Node) + 2*sizeof(void*))
#endif

namespace mcts {

	/**
	 * \brief MctsArgs class
	 * \details 
	 *  options for the MCTS Algorithm
	 *	u_int _depth = depth to explore before running random simulations.
	 *	u_int _timeLimitsimulationPerRoot = time limit in ms
	 *	u_long _simulationPerRoot = number of simulations to run per Root.
	 *	u_int _simulationPerLeaves = number of simulations to run per Leaves.
	 *	u_int _numberOfVisitBeforeExploration = number of visits on a node before expanding its children.
	 *	u_long _maxNumberOfLeaves = maximum number of nodes in the tree, defined by available memory * _percentRAM / 2
	 *	double _percentRAM = percentage of RAM to use by the trees
	 */
	class MctsArgs
	{

		u_int _depth;
		u_int _timeLimitsimulationPerRoot;
		u_long _simulationPerRoot;
		u_int _simulationPerLeaves;
		u_int _numberOfVisitBeforeExploration;
		u_long _maxNumberOfLeaves;
		double _percentRAM;

	public:

		/**
		 * \fn MctsArgs(int depth = 20, int timelimit = 5000, int simulR = 10000000, int simulL = 1, int numVisitExplo = 0)
		 * \brief initialisation of the parameters.
		 * 
		 * \param depth : depth of the maximum search
		 * \param timelimit : time limit for the simulations
		 * \param t : number of root simulations
		 * \param s : number of leaf simulations
		 */
		explicit inline MctsArgs(
			u_int depth = 44,
			u_int timelimit = TIME_SEARCH * 1000,
			u_long simulR = 100000000,
			u_int simulL = 2,
			u_int numVisitExplo = 2,
			double percentRAM = 0.95
			) : _depth(depth), _timeLimitsimulationPerRoot(TIME_SEARCH * 1000), _simulationPerRoot(simulR), _simulationPerLeaves(simulL), _numberOfVisitBeforeExploration(2*numVisitExplo), _percentRAM(percentRAM)
		{
#if defined(_WIN64)
			_maxNumberOfLeaves = static_cast<u_long>(Memory::get_free_memory() * _percentRAM / (DIVIDE));
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
			_maxNumberOfLeaves = static_cast<u_long>(Memory::get_free_memory() * _percentRAM / (DIVIDE));
#else
			std::cout << "Memory limited..." << std::endl;
			_maxNumberOfLeaves = static_cast<u_long>((static_cast<u_long>(1) << 31) * _percentRAM / (DIVIDE)); // maximum size is 2 Go...
#endif

			std::cout << "size of node : " << sizeof(Node) << std::endl;
			std::cout << "max num of leaves : " << Count::format(_maxNumberOfLeaves) << std::endl;
		};

		explicit inline MctsArgs(
			prog_options& options,
			u_int depth = 44
			) : _depth(depth),
				_timeLimitsimulationPerRoot(options.time_to_search*1000),
				_simulationPerRoot(100000000),
				_simulationPerLeaves(options.simul_per_leaves),
				_numberOfVisitBeforeExploration(options.visit_before_expand),
				_percentRAM(options.percent_memory)
		{

			if(options.memory_limited)
				_maxNumberOfLeaves = static_cast<u_long>((static_cast<u_long>(options.hard_memory) << 20) * _percentRAM / (DIVIDE)); // maximum size is 2 Go...
			else
			{
#if defined(_WIN64)
			_maxNumberOfLeaves = static_cast<u_long>(Memory::get_free_memory() * _percentRAM / (DIVIDE));
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
			_maxNumberOfLeaves = static_cast<u_long>(Memory::get_free_memory() * _percentRAM / (DIVIDE));
#else
			std::cout << "Memory limited..." << std::endl;
			_maxNumberOfLeaves = static_cast<u_long>((static_cast<u_long>(1) << 31) * _percentRAM / (DIVIDE)); // maximum size is 2 Go...
#endif
			}

			std::cout << "size of node : " << sizeof(Node) << std::endl;
			std::cout << "max num of leaves : " << Count::format(_maxNumberOfLeaves) << std::endl;
		};


		/**
		 * \fn get_max_depth() 
		 * \brief getter for _depth
		 * 
		 * \return maximum depth
		 */
		inline u_int get_max_depth()
		{
			return _depth;
		};

		/**
		 * \fn set_time_limit_simulation_per_root(u_int t = 2000) 
		 * \brief allow to change the time limit for the simulations between executions
		 */
		inline void set_time_limit_simulation_per_root(u_int t = 2000)
		{
			_timeLimitsimulationPerRoot = t;
		};

		/**
		 * \fn get_time_limit_simulation_per_root() 
		 * \brief getter for _timeLimitsimulationPerRoot
		 * 
		 * \return maximum time limite to run the simulations
		 */
		inline u_int get_time_limit_simulation_per_root()
		{
			return _timeLimitsimulationPerRoot;
		};

		/**
		 * \fn get_max_num_simulation_per_root() 
		 * \brief getter for _simulationPerRoot
		 * 
		 * \return maximum number of simulations to run at the root
		 */
		inline u_long get_max_num_simulation_per_root()
		{
			return _simulationPerRoot;
		};

		/**
		 * \fn get_max_num_simulation_per_leaves() 
		 * \brief getter for _simulationPerLeaves
		 * 
		 * \return maximum number of simulations to run at the leaves
		 */
		inline u_int get_max_num_simulation_per_leaves()
		{
			return _simulationPerLeaves;
		};

		/**
		 * \fn get_number_of_number_of_visit_before_exploration() 
		 * \brief getter for _numberOfVisitBeforeExploration
		 * 
		 * \return number of simulations to run before exploring a node
		 */
		inline u_int get_number_of_number_of_visit_before_exploration()
		{
			return _numberOfVisitBeforeExploration;
		};

		/**
		 * \fn get_max_max_number_of_leaves() 
		 * \brief getter for _maxNumberOfLeaves
		 * 
		 * \return maximum number of leaves in the tree
		 */
		inline u_long get_max_max_number_of_leaves()
		{
			return _maxNumberOfLeaves;
		}

		/**
		 * \fn ~MctsArgs() 
		 * \brief destructor...
		 */
		inline ~MctsArgs() {}
	};

}