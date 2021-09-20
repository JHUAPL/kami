Introduction
============

.. |Generic badge| image:: https://img.shields.io/badge/<SUBJECT>-<STATUS>-<COLOR>.svg
   :target: http://localhost
.. |Build (main)| image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=main
   :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
.. |Build (develop)| image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=develop
   :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
.. |Documentation Status| image:: https://readthedocs.org/projects/kami/badge/?version=latest
   :target: https://kami.readthedocs.io/en/latest/?badge=latest
.. |Release| image:: https://img.shields.io/github/release/JHUAPL/kami.svg
   :target: https://github.com/JHUAPL/spdlog/kami/latest
.. |ConanCenter package| image:: https://repology.org/badge/version-for-repo/conancenter/kami.svg
   :target: https://repology.org/project/kami/versions

Kami is agent-based modeling modern C++.  The objectives in writing
Kami are that it be lightweight, memory-efficient, and fast.  It
should be possible to develop a simple working model in under one
hour of C++ development time.  Accordingly, the platform is modeled
extensively on the `Mesa
<https://mesa.readthedocs.io/en/stable/overview.html>`_ library in
Python, which itself was inspired by the `MASON
<https://cs.gmu.edu/~eclab/projects/mason/>`_ library in Java.

.. toctree::
   :maxdepth: 2
   :hidden:

   tutorial
   api/library_root
   license