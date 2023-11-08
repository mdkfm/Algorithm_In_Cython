from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

module = Extension(
    'decision_tree',
    ['DecisionTree.pyx'],
)

setup(
    name = 'decision_tree',
    cmdclass = {'build_ext': build_ext},
    ext_modules = [module]
)