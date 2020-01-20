#pragma once

#include <torch/csrc/autograd/profiler.h>
#include <torch/csrc/distributed/rpc/py_rref.h>
#include <torch/csrc/distributed/rpc/rpc_agent.h>
#include <torch/csrc/utils/pybind.h>

namespace torch {
namespace distributed {
namespace rpc {

using RRefPtr = c10::intrusive_ptr<RRef>;

py::object toPyObj(const Message& message);

std::shared_ptr<FutureMessage> pyRpcBuiltin(
    RpcAgent& agent,
    const WorkerInfo& dst,
    const std::string& opName,
    const std::shared_ptr<torch::autograd::profiler::RecordFunction>& rf,
    const py::args& args,
    const py::kwargs& kwargs);

std::shared_ptr<FutureMessage> pyRpcPythonUdf(
    RpcAgent& agent,
    const WorkerInfo& dst,
    std::string& pickledPythonUDF,
    std::vector<torch::Tensor>& tensors,
    const std::shared_ptr<torch::autograd::profiler::RecordFunction>& rf);

RRefPtr RemoteBuiltin(
    RpcAgent& agent,
    const WorkerInfo& dst,
    const std::shared_ptr<Operator>& opName,
    const Stack& stack);

PyRRef pyRemotePythonUdf(
    RpcAgent& agent,
    const WorkerInfo& dst,
    std::string& pickledPythonUDF,
    std::vector<torch::Tensor>& tensors,
    const std::shared_ptr<torch::autograd::profiler::RecordFunction>& rf);

} // namespace rpc
} // namespace distributed
} // namespace torch
