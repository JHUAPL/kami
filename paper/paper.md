---
title: 'Kami is Agent-Based Modeling in Modern C++'
tags:
  - C++
  - agent-based model
  - individual-based model
  - social science
  - simulation
  - complex systems theory
- artificial life
authors:
  - name: James P. Howard, II
    orcid: 0000-0003-4530-1547
    equal-contrib: true
    affiliation: 1
affiliations:
  - name: Johns Hopkins Applied Physics Laboratory, USA
    index: 1
date: 23 January 2023
bibliography: paper.bib
---

# Summary

Agent-based models (ABMs) are a type of computational model used
to simulate the behavior of autonomous agents within a system. These
agents can be individuals, groups, organizations, or other entities
that interact with one another and with their environment. One of
the key features of ABMs is that they focus on the micro-level
interactions between individual agents, rather than aggregating
data to study macro-level phenomena. This allows for the examination
of complex behaviors that emerge from the interactions between
agents, such as the spread of a disease or the formation of social
networks. ABMs are often used in fields such as economics, sociology,
and biology to study the behavior of individuals and groups. They
can also be used to simulate the effects of different policies or
interventions on a system.

# Statement of need

There are many different agent-based modeling (ABM) platforms
available for use in Java, Javascript, Python, and other programming
languages. Many others are implemented in domain-specific languages
that allow for the rapid development of complex models. However,
running interpreted, these models are slower than that offered by
compiled systems. There are several application-specific ABMs
available for specific problems, including public health, ecology,
economics, and other fields  [e.g., @5970118, @rutherford2012agent,
@standish2004ecolab, @zhou2010agent]. Kami aims to fill a niche
for implementing a field-neutral, extensible ABM platform in modern
C++, using C++17 as a baseline for requirements.

Kami provides support for multiple agent classes, population
management, scheduling management, and environmental management
classes. The package provides examples of three relatively simple
ABMs: a bank reserves model, a one-dimensional Boltzmann wealth
model, and a two-dimensional Boltzmann wealth model. The package
provides examples of both a minimal ABM implemented with Kami, as
well as a starter ABM, either of which is suitable for beginning a
new investigation using Kami. Finally, the library provides extensive
unit-testing for all of the internal classes.

Kami's interface is heavily influenced by Mesa's interface
[@python-mesa-2020]. However, being written in C++, Kami runs
substantially faster. This allows for faster runs and more runs
within a fixed amount of time. The advantage here is that an ABM
built on the Kami platform is better suited for statistical and
Monte Carlo approaches to modeling.

An interest design note is that Kami does not use any form of
parallel processing due to the complexities of managing random
number generators and providing reproducibility in results for a
given random number seed. However, it is suitable to run as many
instances of Kami-based models simultaneously as hardware threading
can permit. A final design note is that Kami is opinionated in
that it prefers inheritance to composition in model design and
further, templates are not used for metaprogramming.

# References