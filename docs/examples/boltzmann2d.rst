boltzmann2d
===========

This example provides a two-dimensional Boltzmann wealth model (BWM)
as an example of a simple application of the two-dimensional gridded
system.

The BWM is a type of agent-based model used to study the distribution
of wealth among individuals within a population. The model simulates
agents' interactions over time, such as buying and selling goods,
lending and borrowing money, and inheriting wealth. The model is
based on a "wealth-exchange mechanism" which determines the probability
of agents making a wealth exchange with each other, it is often
based on the difference in wealth between agents. The model can be
run for a specified number of time steps, and the resulting wealth
distribution can be analyzed to study the emergence of wealth
inequality and the factors that contribute to it.

For more information on BWMs, please see the boltzmann1d_
example documentation.

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
   * - -y *y_size*
     - Set the number of rows

..  _boltzmann1d: boltzmann1d.html

..  toctree::
