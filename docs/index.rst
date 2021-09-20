Introduction
============

.. |Build (main)| image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=main
   :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
   :alt: Build status (main)
.. |Build (develop)| image:: https://github.com/JHUAPL/kami/actions/workflows/build.yml/badge.svg?branch=develop
   :target: https://github.com/JHUAPL/kami/actions/workflows/build.yml
   :alt: Build status (develop)
.. |Documentation Status| image:: https://readthedocs.org/projects/kami/badge/?version=latest
   :target: https://kami.readthedocs.io/en/latest/?badge=latest
   :alt: Documentation status
.. |Release| image:: https://img.shields.io/github/release/JHUAPL/kami.svg
   :target: https://github.com/JHUAPL/spdlog/kami/latest
   :alt: Release status
.. |ConanCenter package| image:: https://repology.org/badge/version-for-repo/conancenter/kami.svg
   :target: https://repology.org/project/kami/versions
   :alt: ConanCenter status

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