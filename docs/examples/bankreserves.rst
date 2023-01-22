bankreserves
============

This example provides a two-dimensional bank reserves model (BSM)
as an example of a simple application of the reporter classes for
monitoring the internal functioning of the model.

The BSM is a type of computational model that simulates the behavior
of customers and their interactions with a bank. It is used to study
the dynamics of the money supply and the management of reserves by
the bank.

In a BSM, individuals are represented as autonomous agents that
make decisions about saving, borrowing, and repaying loans based
on their individual objectives and constraints. The bank is also
represented as an agent that maintains accounts for each individual.
The interactions between individuals and the bank are simulated
over time, and the model can be used to study the effects of different
reserve requirements policies on the creation of money, borrowing,
lending, and savings.

One of the main advantages of a BSM is that it allows for the
examination of the micro-level interactions between individuals and
the bank, which can provide a more detailed understanding of the
dynamics of the monetary system.

It is important to note that BSMs are a simplified representation
of the real world and may not capture all the nuances of the monetary
system being studied. It's also important to use this model in
conjunction with other methods to fully understand the monetary
system.

.. list-table::
   :widths: 30 70
   :header-rows: 1

   * - Option
     - Description
   * - -c *agent_count*
     - Set the number of agents
   * - -f *output_file_name*
     - Set the JSON report file
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
   * - -w *max_initial_wealth*
     - Set the maximum initial agent wealth

..  toctree::
