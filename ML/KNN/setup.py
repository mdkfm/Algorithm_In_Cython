from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

module = Extension(
    'knn',
    ['knn.pyx'],
)

setup(
    name = 'KNN algorithm',
    cmdclass = {'build_ext': build_ext},
    ext_modules = [module]
)