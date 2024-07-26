#include <windows.h> //move to first line if error

random_device rd;
mt19937 gen(rd());

ll randomNumber(ll from, ll to)
{
    uniform_int_distribution<int> dist(from, to);
    return dist(gen);
}

v randomArray(ll n, ll from, ll to)
{
    v res(n);
    for (ll i = 0; i < n; i++) res[i] = randomNumber(from, to);
    return res;
}

v randomPerm(ll n, bool oneIndex = false)
{
    v perm(n);
    for (ll i = 0; i < n; i++) perm[i] = i + oneIndex;
    random_shuffle(all(perm));
    return perm;
}

void shuffleGraph(vp &edges)
{
    shuffle(all(edges), gen);
    for (auto &x : edges) if (randomNumber(0, 1) == 0) swap(x.f, x.s);
}

vp randomTree(ll n)
{
    v prufer = randomArray(n - 2, 0, n - 1);
    vp edges;
    v degree(n, 1);
    for (ll i = 0; i < n - 2; i++) degree[prufer[i]]++;
    ll ptr = 0;
    while (degree[ptr] != 1) ptr++;
    ll leaf = ptr;
    for (ll i : prufer)
    {
        edges.eb(leaf, i);
        if (--degree[i] == 1 && i < ptr)
            leaf = i;
        else
        {
            ptr++;
            while (degree[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    edges.eb(leaf, n - 1);
    shuffleGraph(edges);
    return edges;
}

vp randomConnectedSimpleGraph(ll n, ll m)
{
    vp res = randomTree(n);
    m -= (n - 1);
    set<p> edges;
    for (auto x : res) edges.insert(x);
    while (m--)
    {
        ll i = 0, j = 0;
        while (i == j || edges.count(p(i,j)) == 1)
        {
            i = randomNumber(0, n - 1);
            j = randomNumber(0, n - 1);
        }
        res.eb(i, j);
        edges.emplace(i, j);
    }
    return res;
}

vp randomSimpleGraph(ll n, ll m)
{
    vp res;
    set<p> edges;
    for (auto x : res) edges.insert(x);
    while (m--)
    {
        ll i = 0, j = 0;
        while (i == j || edges.count(p(i,j)) == 1)
        {
            i = randomNumber(0, n - 1);
            j = randomNumber(0, n - 1);
        }
        res.eb(i, j);
        edges.emplace(i, j);
    }
    return res;
}

vp generateRootedChain(ll n)
{
    v perm = randomPerm(n);
    vp res;
    for (ll i = 0; i < n - 1; i++) res.eb(perm[i], perm[i + 1]);
    shuffle(all(res), gen);
    return res;
}

vp generateRootedStar(ll n, ll center = -1)
{
    if (center == -1) center = randomNumber(0, n - 1);
    vp res;
    for (ll i = 0; i < n; i++) if (i != center) res.eb(i, center);
    shuffle(all(res), gen);
    return res;
}

vv graphFromEdgeArray(ll n, vp &edges)
{
    vv res(n);
    for (auto x : edges)
    {
        res[x.f].pb(x.s);
        res[x.s].pb(x.f);
    }
    return res;
}

vp toRootedTree(vp tree)
{
    ll n = tree.size() + 1;
    vv graph = graphFromEdgeArray(n, tree);
    ll root = randomNumber(0, n - 1);
    stack<p> dfs;
    dfs.emplace(root, -1);
    vb visited(n, false);
    vp res;
    while (!dfs.empty())
    {
        auto top = dfs.top();
        dfs.pop();
        if (visited[top.f]) continue;
        visited[top.f] = true;
        if (top.s != -1) res.pb(top);
        for (ll x: graph[top.f]) dfs.emplace(x, top.f);
    }
    return res;
}

const ll _MAX_PATH_SIZE = 200;
const ll _BUFFER_SIZE = 100;

string _getCurrentDirectory()
{
    char buffer[_MAX_PATH_SIZE] = {0};
    GetModuleFileName(NULL,buffer,_MAX_PATH_SIZE);
    string filePath(buffer);
    ll i = filePath.size() - 1;
    while (filePath[i] != '\\') i--;
    return filePath.substr(0, i);
}

void _writeToPipe(HANDLE &handle, string str)
{
    unsigned long written;
    ll i = 0;
    while (i < str.size())
    {
        ll len = min((ll)_BUFFER_SIZE, (ll)str.size() - i);
        char *inputBuffer = (char*)str.substr(i, len).c_str();
        WriteFile(handle, inputBuffer, len, &written,NULL);
        i += _BUFFER_SIZE;
    }
}

string _readFromPipe(HANDLE &handle)
{
    string output;
    char outputBuffer[_BUFFER_SIZE] = {0};
    unsigned long read;
    while (true)
    {
        ReadFile(handle, outputBuffer, _BUFFER_SIZE, &read, NULL);
        if (read == 0) break;
        output += string(outputBuffer);
    }
    return output;
}

const string _compiler =  "C:\\msys64\\ucrt64\\bin\\g++.exe";

void compileProgram(string fileName)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = NULL;
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    string dir = _getCurrentDirectory();
    string command = _compiler + " " + dir + "\\" + fileName + ".cpp -o " + dir + "\\" + fileName + ".exe";
    CreateProcess(NULL,(char*)command.c_str(),NULL,NULL,false,0,NULL,NULL,&si,&pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

string executeProgram(string fileName, string input)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    string filePath = _getCurrentDirectory() + "\\" + fileName + ".exe";

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = true;
    sa.lpSecurityDescriptor = NULL;

    HANDLE InputPipeHandles[2]; 
    HANDLE OutputPipeHandles[2];
    CreatePipe(&InputPipeHandles[0], &InputPipeHandles[1], &sa, 0);
    CreatePipe(&OutputPipeHandles[0], &OutputPipeHandles[1], &sa, 0);
    SetHandleInformation(InputPipeHandles[1], HANDLE_FLAG_INHERIT, 0);
    SetHandleInformation(OutputPipeHandles[0], HANDLE_FLAG_INHERIT, 0);

    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput = InputPipeHandles[0];
    si.hStdOutput = OutputPipeHandles[1];
    si.hStdError = OutputPipeHandles[1];

    _writeToPipe(InputPipeHandles[1], input);

    CreateProcess((char*)filePath.c_str(), NULL, NULL,NULL, true, 0, NULL,NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(OutputPipeHandles[1]);
    CloseHandle(InputPipeHandles[0]);
    
    return _readFromPipe(OutputPipeHandles[0]);
}
