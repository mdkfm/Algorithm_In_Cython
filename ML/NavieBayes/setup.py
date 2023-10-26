from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

module = Extension(
    'naviebayes',
    ['naviebayes.pyx'],
)

setup(
    name = 'Gaussian Navie Bayes algorithm',
    cmdclass = {'build_ext': build_ext},
    ext_modules = [module]
)