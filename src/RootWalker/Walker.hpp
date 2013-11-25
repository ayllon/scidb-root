#ifndef __WALKER_HPP
#define __WALKER_HPP

#include <memory>
#include <TFile.h>
#include "Data.hpp"
#include "Node.hpp"

namespace raw {
namespace root {
    
class TypeResolver;

/// Visitor interface.
/// This must be implemented by the client, so the Walker can call the corresponding
/// methods.
class IVisitor
{
public:
    /// Called before desdencing into a data member
    /// @param node The node being visited.
    /// @return If it returns false, the walker won't descend into the children
    virtual bool pre(const std::shared_ptr<Node> node) = 0;
    
    /// Called after processing a data member
    /// @param node The node being visited.
    virtual void post(const std::shared_ptr<Node> node) = 0;
    
    /// Called when an element of unknown type is found.
    /// @param node The node being visited.
    virtual void unknown(const std::shared_ptr<Node> node) = 0;
    
    /// Called for a basic type with a name. For instance, object attributes.
    /// @param name The attribute name
    /// @param data The attribute raw data
    virtual void leaf(const std::string& name, const std::shared_ptr<Data> data) = 0;
    
    /// Called for a basic type within an array.
    /// @param index The attribute index within the array
    /// @param data  The attribute raw data
    virtual void leaf(size_t index, const std::shared_ptr<Data> data) = 0;
};

/// Public interface
class Walker
{
public:
    /// Constructor
    /// @param typeResolver A TypeResolver
    Walker(std::shared_ptr<TypeResolver> typeResolver);
    
    /// Perform the walk
    /// @param node Holder to a Root object
    /// @param visitor The implementation of IVisitor
    void walk(const std::shared_ptr<Node> node, IVisitor* visitor);
    
    /// Convenience method to get a child node
    /// i.e.
    /// TFile file(...);
    /// Walker::getNode(Node(file), "rootObj.attr.nestedAttr")
    std::shared_ptr<Node> getChildNode(const std::shared_ptr<Node> node, const std::string& path);
    
protected:
    std::shared_ptr<TypeResolver> typeResolver;
};

}}

#endif // __WALKER_HPP
