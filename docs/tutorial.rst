Tutorial
========

Kami's interface is heavily influenced by Mesa_'s interface.  However,
by being written in C++, Kami runs substantially faster.  This
allows for faster runs and more runs within a fixed amount of time.
The advantage here is that an agent-based model (ABM) built on the
Kami platform is better suited for statistical and Monte Carlo
approaches to modelling.

Model Form
----------

Kami-based models have five key components:

1. Agents, which are objects representing the actors within the model
2. Populations, which are collections of Agents
3. Domains, which provide a representation of "physical" space the Agent inhabits
4. Schedulers, which provide a representation of "time" within the model
5. Model, which are objects connecting Populations, Domains, and Schedulers

In general, a model should have one scheduler, one domain, and some
number of agents.  However, it would not be impossible to have more
than one scheduler or more than one domain.  Because this is
implemented in C++, your agents should subclass Agent and your model
should subclass model.  The schedulers and domains are sufficient
as is for their purposes though custom schedulers and domains are
not unreasonable.

A Minimal ABM
-------------

The minimal ABM starts with the simplest possible agent.  Here, we
create a class called ``MinimalAgent``:

.. code-block:: c++
  :linenos:

    class MinimalAgent : public kami::Agent {
    public:
        kami::AgentID step(std::shared_ptr<kami::Model> model) override {
            return this->get_agent_id();
        }
    };

An ``Agent``, and its subclasses, will automatically inherit an ``AgentID``,
which is the unique identifier for the session.  The only explicit
requirement on the ``Agent`` subclass is a `step()` method that accepts
a ``shared_ptr`` to a ``Model`` and it must return the ``Agent``'s ``AgentID``.
Obviously, an ``Agent`` should do something useful before returning.

The second component is ``MinimalModel:``

.. code-block:: c++
  :linenos:

  class MinimalModel: public kami::Model {
  public:
      MinimalModel() {
          auto sched = std::make_shared<kami::SequentialScheduler>();
          set_scheduler(sched);

          auto pop = std::make_shared<kami::Population>();
          set_population(pop);

          for (auto i = 0; i < 10; i++) {
              auto new_agent = std::make_shared<MinimalAgent>();
              pop->add_agent(new_agent);
          }
      }
  };

The ``MinimalModel`` performs some important tasks that important to do
during the setup or soon thereafter.  In the constructor, first, a
scheduler is created.  The ``SequentialScheduler`` is the simplest
scheduler and has no configuration needed.  Using `set_scheduler()`,
part of the Model class, the scheduler is associated with this
model.  Second, a `Population` is created and associated with this
model with the `set_population()` method.

After this, the constructor initializes 10 ``MinimalAgents`` and adds
them to the population.

.. code-block:: c++
  :linenos:

  int main() {
      auto model = std::make_shared<MinimalModel>();

      for (int i = 0; i < 10; i++)
          model->step();

      return 0;
  }

The last part is our `main()` function.  It creates the `MinimalModel`
then executes its `step()` method 10 times.  The `step()` method, by
default, calls the `step()` method of the scheduler.  In the case of
the ``SequentialScheduler``, it loops over all the ``Agent`` instances in the
``Population`` and executes the associated `step()` method of each ``Agent``.

That is it.  It is the simplest minimal model that can be created
using the Kami platform.  However, for a basis, it is likely better
to use the starter model, included in the examples directory.

..  _Mesa: https://mesa.readthedocs.io

..  toctree::
