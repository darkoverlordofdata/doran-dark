#pragma once
#include <dark/Foundation.h>
#include <xna/xna.h>
#include <assert.h>



type (EcsTeamManager)
{
    Class isa;
    EcsManager* base;
    EcsWorld* World;
    Map* PlayersByTeam;
    Map* TeamByPlayer;
};

method char* GetTeam(EcsTeamManager* self, char* player);
method void SetTeam(EcsTeamManager* self, char* player, char* team);
method Array* GetPlayers(EcsTeamManager* self, char* team);
method void RemoveFromTeam(EcsTeamManager* self, char* player);

delegate (EcsTeamManager, New,          EcsTeamManager*, (EcsTeamManager*));
delegate (EcsTeamManager, ToString,     char*,    (const EcsTeamManager* const));
delegate (EcsTeamManager, Initialize,   void, (EcsTeamManager*));
delegate (EcsTeamManager, GetWorld,     EcsWorld*, (EcsTeamManager*));
delegate (EcsTeamManager, SetWorld,     void, (EcsTeamManager*, EcsWorld*));
delegate (EcsTeamManager, Added,        void, (EcsTeamManager*, EcsEntity*));
delegate (EcsTeamManager, Changed,      void, (EcsTeamManager*, EcsEntity*));
delegate (EcsTeamManager, Deleted,      void, (EcsTeamManager*, EcsEntity*));
delegate (EcsTeamManager, Disabled,     void, (EcsTeamManager*, EcsEntity*));
delegate (EcsTeamManager, Enabled,      void, (EcsTeamManager*, EcsEntity*));


/**
 * EcsTeamManager Vtable
 */
vtable (EcsTeamManager) 
{
    const EcsTeamManagerToString    ToString;
    const ObjectEquals          Equals;
    const ObjectGetHashCode     GetHashCode;
    const ObjectDispose         Dispose;
    const EcsTeamManagerToString    Initialize;
    const EcsTeamManagerGetWorld    GetWorld;
    const EcsTeamManagerSetWorld    SetWorld;
    const EcsTeamManagerAdded       Added;
    const EcsTeamManagerChanged     Changed;
    const EcsTeamManagerDeleted     Deleted;
    const EcsTeamManagerDisabled    Disabled;
    const EcsTeamManagerEnabled     Enabled;
};

static inline vptr(EcsTeamManager);
/**
 * Create the class loader
 */
static inline Class ClassLoadEcsTeamManager(Class base) 
{
    Class cls = createClass(base, EcsTeamManager);
    addMethod(cls, Object,      ToString);
    addMethod(cls, Object,      Equals);
    addMethod(cls, Object,      GetHashCode);
    addMethod(cls, Object,      Dispose);
    addMethod(cls, EcsTeamManager,  Initialize);
    addMethod(cls, EcsTeamManager,  GetWorld);
    addMethod(cls, EcsTeamManager,  SetWorld);
    addMethod(cls, EcsTeamManager,  Added);
    addMethod(cls, EcsTeamManager,  Changed);
    addMethod(cls, EcsTeamManager,  Deleted);
    addMethod(cls, EcsTeamManager,  Disabled);
    addMethod(cls, EcsTeamManager,  Enabled);
    return cls; 
}

method EcsTeamManager* New(EcsTeamManager* self)
{
    self->base = extends(EcsManager);
    self->isa = isa(EcsTeamManager);
    self->PlayersByTeam = new(Map, of(Array));
    self->TeamByPlayer = new(Map);
    return self;
}

method void Initialize(EcsTeamManager* self) { virtual(EcsTeamManager)->Initialize(self); }

method void SetWorld(EcsTeamManager* self, EcsWorld* world)
{
    SetWorld(self->base, world);
}

method EcsWorld* GetWorld(EcsTeamManager* self)
{
    return GetWorld(self->base);
}

method void Added(EcsTeamManager* self, EcsEntity* entity) { virtual(EcsTeamManager)->Added(self, entity); }

method void Changed(EcsTeamManager* self, EcsEntity* entity) { virtual(EcsTeamManager)->Changed(self, entity); }

method void Deleted(EcsTeamManager* self, EcsEntity* entity) { virtual(EcsTeamManager)->Deleted(self, entity); }

method void Disabled(EcsTeamManager* self, EcsEntity* entity) { virtual(EcsTeamManager)->Disabled(self, entity); }

method void Enabled(EcsTeamManager* self, EcsEntity* entity) { virtual(EcsTeamManager)->Enabled(self, entity); }

method char* GetTeam(EcsTeamManager* self, char* player) {
    return Get(self->TeamByPlayer, player);
}

method void SetTeam(EcsTeamManager* self, char* player, char* team) {
    RemoveFromTeam(self, player);

    Put(self->TeamByPlayer, player, team);

    Array* players = Get(self->PlayersByTeam, team);
    if(players == nullptr) {
        players = new(Array);
        Put(self->PlayersByTeam, team, players);
    }
    Add(players, player);
}

method Array* GetPlayers(EcsTeamManager* self, char* team)  {
    return Get(self->PlayersByTeam, team);
}

method void RemoveFromTeam(EcsTeamManager* self, char* player) {
    char* team = Get(self->TeamByPlayer, player);
    if (Remove(self->TeamByPlayer, player)) {
        Array* players = Get(self->PlayersByTeam, team);
        if (players != nullptr) {
            Remove(players, (Object*)player);
        }
    }
}
