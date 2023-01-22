boltzmann1d
===========

This example provides a one-dimensional Boltzmann wealth model (BWM)
as an example of a simple application of the one-dimensional gridded
system.

The BWM is a type of agent-based model used to study the distribution
of wealth among individuals or agents within a population. The model
is named after the physicist Ludwig Boltzmann, who first proposed
a similar model to study the distribution of energy among particles
in a gas.

In a BWM, agents are assigned a certain amount of wealth, and the
model simulates their interactions over time.  These interactions
can include buying and selling goods and services, lending and
borrowing money, and inheriting wealth from other agents.

The key feature of the BWM is that it incorporates a "wealth-exchange
mechanism" which determines the probability of agents making a
wealth exchange with each other. This mechanism is often based on
the difference in wealth between agents, with wealthier agents more
likely to make exchanges with other wealthy agents.

The model can be run for a specified number of time steps, and the
resulting wealth distribution can be analyzed to study the emergence
of wealth inequality and the factors that contribute to it. The
model can also be used to study the effects of different policies
or interventions on the wealth distribution.

The BWM has been used to study a variety of different economic
systems, including capitalist, socialist, and feudal systems.
However, it is important to note that like other agent-based models,
the BWM is a simplified representation of the real world and may
not capture all the nuances of the economic system being studied.

Overall, the BWM is a useful tool for studying the distribution of
wealth and the emergence of wealth inequality in a population. It
can provide insight into the factors that contribute to wealth
inequality and the effects of different policies on the distribution
of wealth.

.. list-table::
   :widths: 30 70
   :header-rows: 1

   * - Option
     - Description
   * - -c *agent_count*
     - Set the number of agents
   * - -l *log_level_option*
     - Set the logging level
   * - -n *max_steps*
     - Set the number of steps to run the model
   * - -s *initial_seed*
     - Set the initial seed
   * - -x *x_size*
     - Set the number of columns

..  toctree::
