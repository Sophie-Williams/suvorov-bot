#include "API.h"
#include "Order.h"
#include "Helpers.h"

namespace API
{

Action::Action(sc2::ActionInterface* action_): m_action(action_)
{
}

void Action::command(const Order& order_)
{
    m_action->UnitCommand(order_.m_assignee, order_.m_id);
}

void Action::command(const Order& order_, const sc2::Point2D& point_)
{
    m_action->UnitCommand(order_.m_assignee, order_.m_id, point_);
}

Observer::Observer(const sc2::ObservationInterface* observer_):
    m_observer(observer_)
{
}

sc2::Units Observer::getUnits(const sc2::Filter& filter_,
    sc2::Unit::Alliance alliance_) const
{
    return m_observer->GetUnits(alliance_, filter_);
}

size_t Observer::countUnitType(sc2::UNIT_TYPEID type_) const
{
    return getUnits(isUnit(type_)).size();
}

const sc2::GameInfo& Observer::gameInfo() const
{
    return m_observer->GetGameInfo();
}

sc2::Point3D Observer::startingLocation() const
{
    return m_observer->GetStartLocation();
}

Query::Query(sc2::QueryInterface* query_): m_query(query_)
{
}

bool Query::canBePlaced(const Order& order_, const sc2::Point2D& point_)
{
    return m_query->Placement(order_.m_id, point_);
}

Interface::Interface(sc2::ActionInterface* action_,
    const sc2::ObservationInterface* observer_, sc2::QueryInterface* query_):
    m_action(action_), m_observer(observer_), m_query(query_)
{}

Action Interface::action() const
{
    return Action(m_action);
}

Observer Interface::observer() const
{
    return Observer(m_observer);
}

Query Interface::query() const
{
    return Query(m_query);
}

} //namespace API

std::unique_ptr<API::Interface> gAPI;