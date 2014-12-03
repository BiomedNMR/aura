backend = 'CUDA';
backendflag = ['-DAURA_BACKEND_', backend];

[pathstr,name,ext] = fileparts(mfilename('fullpath'));
if ~isempty(pathstr)
    pathstr = [pathstr, '/'];
end
% build kernel file
buildstr = ['/usr/local/cuda/bin/nvcc --ptx', ' ', ...
    backendflag, ' ', ...
    ['-I', pathstr, '../../include'], ' ', ...
    [pathstr, 'kernel.cu']];
buildstr
system(buildstr);

% build mex file
mex(backendflag, ' ', ...
    'CXXFLAGS=$CXXFLAGS -fPIC -std=c++0x -Wall', ...
    '-I/usr/local/boost/include', ...
    ['-I', pathstr, '../../include'], ...
    '-I/usr/local/cuda/include', ...
    '-L/usr/local/cuda/lib64', ...
    '-lcuda', '-lcufft', ...
    'mexexample.cpp')

