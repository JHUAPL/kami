Introduction
============


..  image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=main
    :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
    :alt: Build Status (main)
..  image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=develop
    :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
    :alt: Build Status (develop)
..  image:: https://readthedocs.org/projects/kami/badge/?version=latest
    :target: https://kami.readthedocs.io/en/latest/?badge=latest
    :alt: Documentation Status
..  image:: https://img.shields.io/github/release/JHUAPL/kami.svg
    :target: https://github.com/JHUAPL/kami/releases
    :alt: Release Status
..  image:: https://img.shields.io/github/license/JHUAPL/kami
    :alt: License Information

Agent-based models (ABMs) are models for simulating the actions of
individual actors within a provided environment to understand the
behavior of the agents, most individually and collectively.  ABMs
are particularly suited for addressing problems governed by nonlinear
processes or where there is a wide variety of potential responses
an individual agent may provide depending on the environment and
behavior of other agents.  Because of this, ABMs have become powerful
tools in both simulation and modeling, especially in public health
and ecology, where they are also known as individual-based models.
ABMs also provide support in economic, business, robotics, and many
other fields.

Design Objectives
-----------------

Kami provides agent-based modeling modern C++.  The objectives in
writing Kami are that it be lightweight, memory-efficient, and fast.
It should be possible to develop a simple working model in under
one hour of C++ development time.  Accordingly, the platform is
modeled on the Mesa_ library in Python, which itself was inspired
by the MASON_ library in Java.

Many ABM platforms are designed around interaction and real time
observation of the agent dynamics.  Kami does not provide a
visualization interface.  Instead, Kami is meant to be used for
ABMs requiring many runs with different starting conditions.
Accordingly, Kami is single-threaded and multiple cores should be
taken advantage of through multiple parallel runs of the supervising
model.

..  _MASON: https://cs.gmu.edu/~eclab/projects/mason/
..  _Mesa: https://mesa.readthedocs.io

..  toctree::
    :maxdepth: 2
    :hidden:

    index
    installation
    tutorial
    api/library_root
    changelog
    license
