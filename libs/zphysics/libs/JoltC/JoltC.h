#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdalign.h>
//--------------------------------------------------------------------------------------------------
//
// Const
//
//--------------------------------------------------------------------------------------------------
#define JPC_API // TODO: Define this properly

// Always turn on asserts in Debug mode
#if defined(_DEBUG)
    #define JPC_ENABLE_ASSERTS 1
#else
    #define JPC_ENABLE_ASSERTS 0
#endif

#define JPC_PI 3.14159265358979323846f

#define JPC_COLLISION_GROUP_INVALID_GROUP 0xffffffff
#define JPC_COLLISION_GROUP_INVALID_SUB_GROUP 0xffffffff

#define JPC_BODY_ID_INVALID 0xffffffff
#define JPC_BODY_ID_INDEX_BITS 0x007fffff
#define JPC_BODY_ID_BROAD_PHASE_BIT 0x00800000
#define JPC_BODY_ID_SEQUENCE_BITS 0xff000000
#define JPC_BODY_ID_SEQUENCE_SHIFT 24

#ifdef __cplusplus
extern "C" {
#endif

// JPC_JobSystem_Create()
enum
{
    JPC_MAX_PHYSICS_JOBS     = 2048,
    JPC_MAX_PHYSICS_BARRIERS = 8
};

typedef uint8_t JPC_ShapeType;
enum
{
    JPC_SHAPE_TYPE_CONVEX       = 0,
    JPC_SHAPE_TYPE_COMPOUND     = 1,
    JPC_SHAPE_TYPE_DECORATED    = 2,
    JPC_SHAPE_TYPE_MESH         = 3,
    JPC_SHAPE_TYPE_HEIGHT_FIELD = 4,
    JPC_SHAPE_TYPE_USER1        = 5,
    JPC_SHAPE_TYPE_USER2        = 6,
    JPC_SHAPE_TYPE_USER3        = 7,
    JPC_SHAPE_TYPE_USER4        = 8
};

typedef uint8_t JPC_ShapeSubType;
enum
{
    JPC_SHAPE_SUB_TYPE_SPHERE                = 0,
    JPC_SHAPE_SUB_TYPE_BOX                   = 1,
    JPC_SHAPE_SUB_TYPE_TRIANGLE              = 2,
    JPC_SHAPE_SUB_TYPE_CAPSULE               = 3,
    JPC_SHAPE_SUB_TYPE_TAPERED_CAPSULE       = 4,
    JPC_SHAPE_SUB_TYPE_CYLINDER              = 5,
    JPC_SHAPE_SUB_TYPE_CONVEX_HULL           = 6,
    JPC_SHAPE_SUB_TYPE_STATIC_COMPOUND       = 7,
    JPC_SHAPE_SUB_TYPE_MUTABLE_COMPOUND      = 8,
    JPC_SHAPE_SUB_TYPE_ROTATED_TRANSLATED    = 9,
    JPC_SHAPE_SUB_TYPE_SCALED                = 10,
    JPC_SHAPE_SUB_TYPE_OFFSET_CENTER_OF_MASS = 11,
    JPC_SHAPE_SUB_TYPE_MESH                  = 12,
    JPC_SHAPE_SUB_TYPE_HEIGHT_FIELD          = 13,
    JPC_SHAPE_SUB_TYPE_USER1                 = 14,
    JPC_SHAPE_SUB_TYPE_USER2                 = 15,
    JPC_SHAPE_SUB_TYPE_USER3                 = 16,
    JPC_SHAPE_SUB_TYPE_USER4                 = 17,
    JPC_SHAPE_SUB_TYPE_USER5                 = 18,
    JPC_SHAPE_SUB_TYPE_USER6                 = 19,
    JPC_SHAPE_SUB_TYPE_USER7                 = 20,
    JPC_SHAPE_SUB_TYPE_USER8                 = 21
};

typedef uint8_t JPC_MotionType;
enum
{
    JPC_MOTION_TYPE_STATIC    = 0,
    JPC_MOTION_TYPE_KINEMATIC = 1,
    JPC_MOTION_TYPE_DYNAMIC   = 2
};

typedef uint8_t JPC_MotionQuality;
enum
{
    JPC_MOTION_QUALITY_DISCRETE    = 0,
    JPC_MOTION_QUALITY_LINEAR_CAST = 1
};

typedef uint8_t JPC_OverrideMassProperties;
enum
{
    JPC_OVERRIDE_MASS_PROPS_CALC_MASS_INERTIA     = 0,
    JPC_OVERRIDE_MASS_PROPS_CALC_INERTIA          = 1,
    JPC_OVERRIDE_MASS_PROPS_MASS_INERTIA_PROVIDED = 2
};

typedef enum JPC_Activation
{
    JPC_ACTIVATION_ACTIVATE      = 0,
    JPC_ACTIVATION_DONT_ACTIVATE = 1,
    _JPC_ACTIVATION_FORCEU32     = 0x7fffffff
} JPC_Activation;

typedef enum JPC_ValidateResult
{
    JPC_VALIDATE_RESULT_ACCEPT_ALL_CONTACTS = 0,
    JPC_VALIDATE_RESULT_ACCEPT_CONTACT      = 1,
    JPC_VALIDATE_RESULT_REJECT_CONTACT      = 2,
    JPC_VALIDATE_RESULT_REJECT_ALL_CONTACTS = 3,
    _JPC_VALIDATE_RESULT_FORCEU32           = 0x7fffffff
} JPC_ValidateResult;
//--------------------------------------------------------------------------------------------------
//
// Types
//
//--------------------------------------------------------------------------------------------------
typedef uint16_t JPC_ObjectLayer;
typedef uint8_t  JPC_BroadPhaseLayer;
typedef uint64_t JPC_MutexMask;

// TODO: Consider using structures for IDs
typedef uint32_t JPC_BodyID;
typedef uint32_t JPC_SubShapeID;
typedef uint32_t JPC_CollisionGroupID;
typedef uint32_t JPC_CollisionSubGroupID;

// Must be 16 byte aligned
typedef void *(*JPC_AllocateFunction)(size_t in_size);
typedef void (*JPC_FreeFunction)(void *in_block);

typedef void *(*JPC_AlignedAllocateFunction)(size_t in_size, size_t in_alignment);
typedef void (*JPC_AlignedFreeFunction)(void *in_block);

typedef bool
(*JPC_ObjectLayerPairFilter)(JPC_ObjectLayer in_layer1, JPC_ObjectLayer in_layer2);

typedef bool
(*JPC_ObjectVsBroadPhaseLayerFilter)(JPC_ObjectLayer in_layer1, JPC_BroadPhaseLayer in_layer2);
//--------------------------------------------------------------------------------------------------
//
// Opaque Types
//
//--------------------------------------------------------------------------------------------------
typedef struct JPC_TempAllocator     JPC_TempAllocator;
typedef struct JPC_JobSystem         JPC_JobSystem;
typedef struct JPC_BodyInterface     JPC_BodyInterface;
typedef struct JPC_BodyLockInterface JPC_BodyLockInterface;

typedef struct JPC_ShapeSettings               JPC_ShapeSettings;
typedef struct JPC_ConvexShapeSettings         JPC_ConvexShapeSettings;
typedef struct JPC_BoxShapeSettings            JPC_BoxShapeSettings;
typedef struct JPC_SphereShapeSettings         JPC_SphereShapeSettings;
typedef struct JPC_TriangleShapeSettings       JPC_TriangleShapeSettings;
typedef struct JPC_CapsuleShapeSettings        JPC_CapsuleShapeSettings;
typedef struct JPC_TaperedCapsuleShapeSettings JPC_TaperedCapsuleShapeSettings;
typedef struct JPC_CylinderShapeSettings       JPC_CylinderShapeSettings;
typedef struct JPC_ConvexHullShapeSettings     JPC_ConvexHullShapeSettings;

typedef struct JPC_PhysicsSystem JPC_PhysicsSystem;
typedef struct JPC_SharedMutex   JPC_SharedMutex;

typedef struct JPC_Shape           JPC_Shape;
typedef struct JPC_PhysicsMaterial JPC_PhysicsMaterial;
typedef struct JPC_GroupFilter     JPC_GroupFilter;
//--------------------------------------------------------------------------------------------------
//
// Structures
//
//--------------------------------------------------------------------------------------------------
// NOTE: Needs to be kept in sync with JPH::MassProperties
typedef struct JPC_MassProperties
{
    float             mass;
    alignas(16) float inertia[16];
} JPC_MassProperties;

// NOTE: Needs to be kept in sync with JPH::MotionProperties
typedef struct JPC_MotionProperties
{
    alignas(16) float linear_velocity[4];
    alignas(16) float angular_velocity[4];
    alignas(16) float inv_inertia_diagnonal[4];
    alignas(16) float inertia_rotation[4];

    float             force[3];
    float             torque[3];
    float             inv_mass;
    float             linear_damping;
    float             angular_daming;
    float             max_linear_velocity;
    float             max_angular_velocity;
    float             gravity_factor;
    uint32_t          index_in_active_bodies;
    uint32_t          island_index;

    JPC_MotionQuality motion_quality;
    bool              allow_sleeping;

    float             reserved[13];

#if JPC_ENABLE_ASSERTS == 1
    JPC_MotionType    cached_motion_type;
#endif
} JPC_MotionProperties;

// NOTE: Needs to be kept in sync with JPH::CollisionGroup
typedef struct JPC_CollisionGroup
{
    const JPC_GroupFilter *  filter;
    JPC_CollisionGroupID     group_id;
    JPC_CollisionSubGroupID  sub_group_id;
} JPC_CollisionGroup;

// NOTE: Needs to be kept in sync with JPH::BodyCreationSettings
typedef struct JPC_BodyCreationSettings
{
    alignas(16) float          position[4];
    alignas(16) float          rotation[4];
    alignas(16) float          linear_velocity[4];
    alignas(16) float          angular_velocity[4];
    uint64_t                   user_data;
    JPC_ObjectLayer            object_layer;
    JPC_CollisionGroup         collision_group;
    JPC_MotionType             motion_type;
    bool                       allow_dynamic_or_kinematic;
    bool                       is_sensor;
    JPC_MotionQuality          motion_quality;
    bool                       allow_sleeping;
    float                      friction;
    float                      restitution;
    float                      linear_damping;
    float                      angular_damping;
    float                      max_linear_velocity;
    float                      max_angular_velocity;
    float                      gravity_factor;
    JPC_OverrideMassProperties override_mass_properties;
    float                      inertia_multiplier;
    JPC_MassProperties         mass_properties_override;
    const void *               reserved;
    const JPC_Shape *          shape;
} JPC_BodyCreationSettings;

// NOTE: Needs to be kept in sync with JPH::Body
typedef struct JPC_Body
{
    alignas(16) float     position[4];
    alignas(16) float     rotation[4];
    alignas(16) float     bounds_min[4];
    alignas(16) float     bounds_max[4];

    JPC_Shape *           shape;
    JPC_MotionProperties *motion_properties;
    uint64_t              user_data;
    JPC_CollisionGroup    collision_group;

    float                 friction;
    float                 restitution;
    JPC_BodyID            id;

    JPC_ObjectLayer       object_layer;

    JPC_BroadPhaseLayer   broad_phase_layer;
    JPC_MotionType        motion_type;
    uint8_t               flags;
} JPC_Body;

// NOTE: Needs to be kept in sync with JPH::SubShapeIDCreator
typedef struct JPC_SubShapeIDCreator
{
    JPC_SubShapeID id;
    uint32_t       current_bit;
} JPC_SubShapeIDCreator;

// NOTE: Needs to be kept in sync with JPH::SubShapeIDPair
typedef struct JPC_SubShapeIDPair
{
    JPC_BodyID     body1_id;
    JPC_SubShapeID sub_shape1_id;
    JPC_BodyID     body2_id;
    JPC_SubShapeID sub_shape2_id;
} JPC_SubShapeIDPair;

// NOTE: Needs to be kept in sync with JPH::ContactManifold
typedef struct JPC_ContactManifold
{
    alignas(16) float    world_space_normal[4];
    alignas(16) float    penetration_depth;
    JPC_SubShapeID       sub_shape1_id;
    JPC_SubShapeID       sub_shape2_id;
    alignas(16) uint32_t num_points1;
    alignas(16) float    world_space_contact_points1[64][4];
    alignas(16) uint32_t num_points2;
    alignas(16) float    world_space_contact_points2[64][4];
} JPC_ContactManifold;

// NOTE: Needs to be kept in sync with JPH::ContactSettings
typedef struct JPC_ContactSettings
{
    float combined_friction;
    float combined_restitution;
    bool  is_sensor;
} JPC_ContactSettings;

// NOTE: Needs to be kept in sync with JPH::CollideShapeResult
typedef struct JPC_CollideShapeResult
{
    alignas(16) float    contact_point1[4];
    alignas(16) float    contact_point2[4];
    alignas(16) float    penetration_axis[4];
    float                penetration_depth;
    JPC_SubShapeID       sub_shape1_id;
    JPC_SubShapeID       sub_shape2_id;
    JPC_BodyID           body2_id;
    alignas(16) uint32_t num_face_points1;
    alignas(16) float    shape1_face[32][4];
    alignas(16) uint32_t num_face_points2;
    alignas(16) float    shape2_face[32][4];
} JPC_CollideShapeResult;

// NOTE: Needs to be kept in sync with JPH::BroadPhaseLayerInterface
typedef struct JPC_BroadPhaseLayerInterfaceVTable
{
    const void *reserved0;
    const void *reserved1;

    uint32_t
    (*GetNumBroadPhaseLayers)(const void *in_self);

    JPC_BroadPhaseLayer
    (*GetBroadPhaseLayer)(const void *in_self, JPC_ObjectLayer in_layer);
} JPC_BroadPhaseLayerInterfaceVTable;

// NOTE: Needs to be kept in sync with JPH::BodyActivationListener
typedef struct JPC_BodyActivationListenerVTable
{
    const void *reserved0;
    const void *reserved1;

    void
    (*OnBodyActivated)(void *in_self, const JPC_BodyID *in_body_id, uint64_t in_user_data);

    void
    (*OnBodyDeactivated)(void *in_self, const JPC_BodyID *in_body_id, uint64_t in_user_data);
} JPC_BodyActivationListenerVTable;

// NOTE: Needs to be kept in sync with JPH::ContactListener
typedef struct JPC_ContactListenerVTable
{
    const void *reserved0;
    const void *reserved1;

    JPC_ValidateResult
    (*OnContactValidate)(void *in_self,
                         const JPC_Body *in_body1,
                         const JPC_Body *in_body2,
                         const JPC_CollideShapeResult *in_collision_result);
    void
    (*OnContactAdded)(void *in_self,
                      const JPC_Body *in_body1,
                      const JPC_Body *in_body2,
                      const JPC_ContactManifold *in_manifold,
                      JPC_ContactSettings *io_settings);
    void
    (*OnContactPersisted)(void *in_self,
                          const JPC_Body *in_body1,
                          const JPC_Body *in_body2,
                          const JPC_ContactManifold *in_manifold,
                          JPC_ContactSettings *io_settings);
    void
    (*OnContactRemoved)(void *in_self, const JPC_SubShapeIDPair *in_sub_shape_pair);
} JPC_ContactListenerVTable;

// NOTE: Needs to be kept in sync with JPH::TransformedShape
typedef struct JPC_TransformedShape
{
    alignas(16) float     shape_position_com[4];
    alignas(16) float     shape_rotation[4];
    const JPC_Shape *     shape;
    float                 shape_scale[3];
    JPC_BodyID            body_id;
    JPC_SubShapeIDCreator sub_shape_id_creator;
} JPC_TransformedShape;

// NOTE: Needs to be kept in sync with JPH::BodyLockRead
typedef struct JPC_BodyLockRead
{
    const JPC_BodyLockInterface *lock_interface;
    JPC_SharedMutex *            mutex;
    const JPC_Body *             body;
} JPC_BodyLockRead;

// NOTE: Needs to be kept in sync with JPH::BodyLockWrite
typedef struct JPC_BodyLockWrite
{
    const JPC_BodyLockInterface *lock_interface;
    JPC_SharedMutex *            mutex;
    JPC_Body *                   body;
} JPC_BodyLockWrite;

// NOTE: Needs to be kept in sync with JPH::BodyLockMultiRead
typedef struct JPC_BodyLockMultiRead
{
    const JPC_BodyLockInterface *lock_interface;
    JPC_MutexMask                mutex_mask;
    const JPC_BodyID *           body_ids;
    int                          num_body_ids;
} JPC_BodyLockMultiRead;

// NOTE: Needs to be kept in sync with JPH::BodyLockMultiWrite
typedef struct JPC_BodyLockMultiWrite
{
    const JPC_BodyLockInterface *lock_interface;
    JPC_MutexMask                mutex_mask;
    const JPC_BodyID *           body_ids;
    int                          num_body_ids;
} JPC_BodyLockMultiWrite;
//--------------------------------------------------------------------------------------------------
//
// Misc functions
//
//--------------------------------------------------------------------------------------------------
JPC_API void
JPC_RegisterDefaultAllocator(void);

JPC_API void
JPC_RegisterCustomAllocator(JPC_AllocateFunction in_alloc,
                            JPC_FreeFunction in_free,
                            JPC_AlignedAllocateFunction in_aligned_alloc,
                            JPC_AlignedFreeFunction in_aligned_free);
JPC_API void
JPC_CreateFactory(void);

JPC_API void
JPC_DestroyFactory(void);

JPC_API void
JPC_RegisterTypes(void);

JPC_API void
JPC_BodyCreationSettings_Init(JPC_BodyCreationSettings *out_settings);

JPC_API void
JPC_BodyCreationSettings_InitSimple(JPC_BodyCreationSettings *out_settings,
                                    const JPC_Shape *in_shape,
                                    const float in_position[3],
                                    const float in_rotation[4],
                                    JPC_MotionType in_motion_type,
                                    JPC_ObjectLayer in_layer);
//--------------------------------------------------------------------------------------------------
//
// JPC_MotionProperties
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_MotionQuality
JPC_MotionProperties_GetMotionQuality(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetMotionQuality(JPC_MotionProperties *in_properties,
                                      JPC_MotionQuality in_motion_quality);
JPC_API void
JPC_MotionProperties_GetLinearVelocity(const JPC_MotionProperties *in_properties,
                                       float out_linear_velocity[3]);
JPC_API void
JPC_MotionProperties_SetLinearVelocity(JPC_MotionProperties *in_properties,
                                       const float in_linear_velocity[3]);
JPC_API void
JPC_MotionProperties_SetLinearVelocityClamped(JPC_MotionProperties *in_properties,
                                              const float in_linear_velocity[3]);
JPC_API void
JPC_MotionProperties_SetAngularVelocity(JPC_MotionProperties *in_properties,
                                        const float in_angular_velocity[3]);
JPC_API void
JPC_MotionProperties_SetAngularVelocityClamped(JPC_MotionProperties *in_properties,
                                               const float in_angular_velocity[3]);
JPC_API void
JPC_MotionProperties_MoveKinematic(JPC_MotionProperties *in_properties,
                                   const float in_delta_position[3],
                                   const float in_delta_rotation[4],
                                   float in_delta_time);
JPC_API void
JPC_MotionProperties_ClampLinearVelocity(JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_ClampAngularVelocity(JPC_MotionProperties *in_properties);

JPC_API float
JPC_MotionProperties_GetLinearDamping(JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetLinearDamping(JPC_MotionProperties *in_properties,
                                      float in_linear_damping);
JPC_API float
JPC_MotionProperties_GetAngularDamping(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetAngularDamping(JPC_MotionProperties *in_properties,
                                       float in_angular_damping);
JPC_API float
JPC_MotionProperties_GetGravityFactor(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetGravityFactor(JPC_MotionProperties *in_properties,
                                      float in_gravity_factor);
JPC_API void
JPC_MotionProperties_SetMassProperties(JPC_MotionProperties *in_properties,
                                       const JPC_MassProperties *in_mass_properties);
JPC_API float
JPC_MotionProperties_GetInverseMass(const JPC_MotionProperties *in_properties);

JPC_API float
JPC_MotionProperties_GetInverseMassUnchecked(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetInverseMass(JPC_MotionProperties *in_properties, float in_inv_mass);

JPC_API void
JPC_MotionProperties_GetInverseInertiaDiagonal(const JPC_MotionProperties *in_properties,
                                               float out_inverse_inertia_diagonal[3]);
JPC_API void
JPC_MotionProperties_GetInertiaRotation(const JPC_MotionProperties *in_properties,
                                        float out_inertia_rotation[4]);
JPC_API void
JPC_MotionProperties_SetInverseInertia(JPC_MotionProperties *in_properties,
                                       const float in_diagonal[3],
                                       const float in_rotation[4]);
JPC_API void
JPC_MotionProperties_GetLocalSpaceInverseInertia(const JPC_MotionProperties *in_properties,
                                                 float out_matrix[16]);
JPC_API void
JPC_MotionProperties_GetLocalSpaceInverseInertiaUnchecked(const JPC_MotionProperties *in_properties,
                                                          float out_matrix[16]);
JPC_API void
JPC_MotionProperties_GetInverseInertiaForRotation(const JPC_MotionProperties *in_properties,
                                                  const float in_rotation_matrix[4],
                                                  float out_matrix[16]);
JPC_API void
JPC_MotionProperties_MultiplyWorldSpaceInverseInertiaByVector(JPC_MotionProperties *in_properties,
                                                              const float in_body_rotation[4],
                                                              const float in_vector[3],
                                                              float out_vector[3]);
JPC_API void
JPC_MotionProperties_GetPointVelocityCOM(const JPC_MotionProperties *in_properties,
                                         const float in_point_relative_to_com[3],
                                         float out_point[3]);
JPC_API float
JPC_MotionProperties_GetMaxLinearVelocity(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetMaxLinearVelocity(JPC_MotionProperties *in_properties,
                                          float in_max_linear_velocity);
JPC_API float
JPC_MotionProperties_GetMaxAngularVelocity(const JPC_MotionProperties *in_properties);

JPC_API void
JPC_MotionProperties_SetMaxAngularVelocity(JPC_MotionProperties *in_properties,
                                           float in_max_angular_velocity);
JPC_API void
JPC_MotionProperties_AddLinearVelocityStep(JPC_MotionProperties *in_properties,
                                           const float in_linear_velocity_change[3]);
JPC_API void
JPC_MotionProperties_SubLinearVelocityStep(JPC_MotionProperties *in_properties,
                                           const float in_linear_velocity_change[3]);
JPC_API void
JPC_MotionProperties_AddAngularVelocityStep(JPC_MotionProperties *in_properties,
                                            const float in_linear_angular_change[3]);
JPC_API void
JPC_MotionProperties_SubAngularVelocityStep(JPC_MotionProperties *in_properties,
                                            const float in_linear_angular_change[3]);
//--------------------------------------------------------------------------------------------------
//
// JPC_CollisionGroup
//
//--------------------------------------------------------------------------------------------------
JPC_API void
JPC_CollisionGroup_Init(JPC_CollisionGroup *out_group);
//--------------------------------------------------------------------------------------------------
//
// JPC_TempAllocator
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_TempAllocator *
JPC_TempAllocator_Create(uint32_t in_size);

JPC_API void
JPC_TempAllocator_Destroy(JPC_TempAllocator *in_allocator);
//--------------------------------------------------------------------------------------------------
//
// JPC_JobSystem
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_JobSystem *
JPC_JobSystem_Create(uint32_t in_max_jobs, uint32_t in_max_barriers, int in_num_threads);

JPC_API void
JPC_JobSystem_Destroy(JPC_JobSystem *in_job_system);
//--------------------------------------------------------------------------------------------------
//
// JPC_PhysicsSystem
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_PhysicsSystem *
JPC_PhysicsSystem_Create(void);

JPC_API void
JPC_PhysicsSystem_Destroy(JPC_PhysicsSystem *in_physics_system);

JPC_API void
JPC_PhysicsSystem_Init(JPC_PhysicsSystem *in_physics_system,
                       uint32_t in_max_bodies,
                       uint32_t in_num_body_mutexes,
                       uint32_t in_max_body_pairs,
                       uint32_t in_max_contact_constraints,
                       const void *in_broad_phase_layer_interface,
                       JPC_ObjectVsBroadPhaseLayerFilter in_object_vs_broad_phase_layer_filter,
                       JPC_ObjectLayerPairFilter in_object_layer_pair_filter);
JPC_API void
JPC_PhysicsSystem_SetBodyActivationListener(JPC_PhysicsSystem *in_physics_system, void *in_listener);

JPC_API void *
JPC_PhysicsSystem_GetBodyActivationListener(const JPC_PhysicsSystem *in_physics_system);

JPC_API void
JPC_PhysicsSystem_SetContactListener(JPC_PhysicsSystem *in_physics_system, void *in_listener);

JPC_API void *
JPC_PhysicsSystem_GetContactListener(const JPC_PhysicsSystem *in_physics_system);

JPC_API uint32_t
JPC_PhysicsSystem_GetNumBodies(const JPC_PhysicsSystem *in_physics_system);

JPC_API uint32_t
JPC_PhysicsSystem_GetNumActiveBodies(const JPC_PhysicsSystem *in_physics_system);

JPC_API uint32_t
JPC_PhysicsSystem_GetMaxBodies(const JPC_PhysicsSystem *in_physics_system);

JPC_API JPC_BodyInterface *
JPC_PhysicsSystem_GetBodyInterface(JPC_PhysicsSystem *in_physics_system);

JPC_API void
JPC_PhysicsSystem_OptimizeBroadPhase(JPC_PhysicsSystem *in_physics_system);

JPC_API void
JPC_PhysicsSystem_Update(JPC_PhysicsSystem *in_physics_system,
                         float in_delta_time,
                         int in_collision_steps,
                         int in_integration_sub_steps,
                         JPC_TempAllocator *in_temp_allocator,
                         JPC_JobSystem *in_job_system);

JPC_API const JPC_BodyLockInterface *
JPC_PhysicsSystem_GetBodyLockInterface(const JPC_PhysicsSystem *in_physics_system);

JPC_API JPC_Body **
JPC_PhysicsSystem_GetBodiesUnsafe(JPC_PhysicsSystem *in_physics_system);
//--------------------------------------------------------------------------------------------------
//
// JPC_BodyLock*
//
//--------------------------------------------------------------------------------------------------
void JPC_API
JPC_BodyLockRead_Lock(JPC_BodyLockRead *out_lock,
                      const JPC_BodyLockInterface *in_lock_interface,
                      JPC_BodyID in_body_id);
void JPC_API
JPC_BodyLockRead_Unlock(JPC_BodyLockRead *io_lock);

void JPC_API
JPC_BodyLockWrite_Lock(JPC_BodyLockWrite *out_lock,
                       const JPC_BodyLockInterface *in_lock_interface,
                       JPC_BodyID in_body_id);
void JPC_API
JPC_BodyLockWrite_Unlock(JPC_BodyLockWrite *io_lock);
//--------------------------------------------------------------------------------------------------
//
// JPC_ShapeSettings
//
//--------------------------------------------------------------------------------------------------
JPC_API void
JPC_ShapeSettings_AddRef(JPC_ShapeSettings *in_settings);

JPC_API void
JPC_ShapeSettings_Release(JPC_ShapeSettings *in_settings);

JPC_API uint32_t
JPC_ShapeSettings_GetRefCount(const JPC_ShapeSettings *in_settings);

JPC_API JPC_Shape *
JPC_ShapeSettings_CreateShape(const JPC_ShapeSettings *in_settings);

JPC_API uint64_t
JPC_ShapeSettings_GetUserData(const JPC_ShapeSettings *in_settings);

JPC_API void
JPC_ShapeSettings_SetUserData(JPC_ShapeSettings *in_settings, uint64_t in_user_data);
//--------------------------------------------------------------------------------------------------
//
// JPC_ConvexShapeSettings (-> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API const JPC_PhysicsMaterial *
JPC_ConvexShapeSettings_GetMaterial(const JPC_ConvexShapeSettings *in_settings);

JPC_API void
JPC_ConvexShapeSettings_SetMaterial(JPC_ConvexShapeSettings *in_settings,
                                    const JPC_PhysicsMaterial *in_material);

JPC_API float
JPC_ConvexShapeSettings_GetDensity(const JPC_ConvexShapeSettings *in_settings);

JPC_API void
JPC_ConvexShapeSettings_SetDensity(JPC_ConvexShapeSettings *in_settings, float in_density);
//--------------------------------------------------------------------------------------------------
//
// JPC_BoxShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_BoxShapeSettings *
JPC_BoxShapeSettings_Create(const float in_half_extent[3]);

JPC_API void
JPC_BoxShapeSettings_GetHalfExtent(const JPC_BoxShapeSettings *in_settings, float out_half_extent[3]);

JPC_API void
JPC_BoxShapeSettings_SetHalfExtent(JPC_BoxShapeSettings *in_settings, const float in_half_extent[3]);

JPC_API float
JPC_BoxShapeSettings_GetConvexRadius(const JPC_BoxShapeSettings *in_settings);

JPC_API void
JPC_BoxShapeSettings_SetConvexRadius(JPC_BoxShapeSettings *in_settings, float in_convex_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_SphereShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_SphereShapeSettings *
JPC_SphereShapeSettings_Create(float in_radius);

JPC_API float
JPC_SphereShapeSettings_GetRadius(const JPC_SphereShapeSettings *in_settings);

JPC_API void
JPC_SphereShapeSettings_SetRadius(JPC_SphereShapeSettings *in_settings, float in_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_TriangleShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_TriangleShapeSettings *
JPC_TriangleShapeSettings_Create(const float in_v1[3], const float in_v2[3], const float in_v3[3]);

JPC_API void
JPC_TriangleShapeSettings_SetVertices(JPC_TriangleShapeSettings *in_settings,
                                      const float in_v1[3],
                                      const float in_v2[3],
                                      const float in_v3[3]);
JPC_API void
JPC_TriangleShapeSettings_GetVertices(const JPC_TriangleShapeSettings *in_settings,
                                      float out_v1[3],
                                      float out_v2[3],
                                      float out_v3[3]);
JPC_API float
JPC_TriangleShapeSettings_GetConvexRadius(const JPC_TriangleShapeSettings *in_settings);

JPC_API void
JPC_TriangleShapeSettings_SetConvexRadius(JPC_TriangleShapeSettings *in_settings,
                                          float in_convex_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_CapsuleShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_CapsuleShapeSettings *
JPC_CapsuleShapeSettings_Create(float in_half_height_of_cylinder, float in_radius);

JPC_API float
JPC_CapsuleShapeSettings_GetHalfHeightOfCylinder(const JPC_CapsuleShapeSettings *in_settings);

JPC_API void
JPC_CapsuleShapeSettings_SetHalfHeightOfCylinder(JPC_CapsuleShapeSettings *in_settings,
                                                 float in_half_height_of_cylinder);
JPC_API float
JPC_CapsuleShapeSettings_GetRadius(const JPC_CapsuleShapeSettings *in_settings);

JPC_API void
JPC_CapsuleShapeSettings_SetRadius(JPC_CapsuleShapeSettings *in_settings, float in_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_TaperedCapsuleShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_TaperedCapsuleShapeSettings *
JPC_TaperedCapsuleShapeSettings_Create(float in_half_height, float in_top_radius, float in_bottom_radius);

JPC_API float
JPC_TaperedCapsuleShapeSettings_GetHalfHeightOfTaperedCylinder(const JPC_TaperedCapsuleShapeSettings *in_settings);

JPC_API void
JPC_TaperedCapsuleShapeSettings_SetHalfHeightOfTaperedCylinder(JPC_TaperedCapsuleShapeSettings *in_settings,
                                                               float in_half_height);
JPC_API float
JPC_TaperedCapsuleShapeSettings_GetTopRadius(const JPC_TaperedCapsuleShapeSettings *in_settings);

JPC_API void
JPC_TaperedCapsuleShapeSettings_SetTopRadius(JPC_TaperedCapsuleShapeSettings *in_settings, float in_top_radius);

JPC_API float
JPC_TaperedCapsuleShapeSettings_GetBottomRadius(const JPC_TaperedCapsuleShapeSettings *in_settings);

JPC_API void
JPC_TaperedCapsuleShapeSettings_SetBottomRadius(JPC_TaperedCapsuleShapeSettings *in_settings,
                                                float in_bottom_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_CylinderShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_CylinderShapeSettings *
JPC_CylinderShapeSettings_Create(float in_half_height, float in_radius);

JPC_API float
JPC_CylinderShapeSettings_GetConvexRadius(const JPC_CylinderShapeSettings *in_settings);

JPC_API void
JPC_CylinderShapeSettings_SetConvexRadius(JPC_CylinderShapeSettings *in_settings, float in_convex_radius);

JPC_API float
JPC_CylinderShapeSettings_GetHalfHeight(const JPC_CylinderShapeSettings *in_settings);

JPC_API void
JPC_CylinderShapeSettings_SetHalfHeight(JPC_CylinderShapeSettings *in_settings, float in_half_height);

JPC_API float
JPC_CylinderShapeSettings_GetRadius(const JPC_CylinderShapeSettings *in_settings);

JPC_API void
JPC_CylinderShapeSettings_SetRadius(JPC_CylinderShapeSettings *in_settings, float in_radius);
//--------------------------------------------------------------------------------------------------
//
// JPC_ConvexHullShapeSettings (-> JPC_ConvexShapeSettings -> JPC_ShapeSettings)
//
//--------------------------------------------------------------------------------------------------
/// `in_points` needs to be aligned to 16 bytes
JPC_API JPC_ConvexHullShapeSettings *
JPC_ConvexHullShapeSettings_Create(const float in_points[][4], int in_num_points);

JPC_API float
JPC_ConvexHullShapeSettings_GetMaxConvexRadius(const JPC_ConvexHullShapeSettings *in_settings);

JPC_API void
JPC_ConvexHullShapeSettings_SetMaxConvexRadius(JPC_ConvexHullShapeSettings *in_settings,
                                               float in_max_convex_radius);
JPC_API float
JPC_ConvexHullShapeSettings_GetMaxErrorConvexRadius(const JPC_ConvexHullShapeSettings *in_settings);

JPC_API void
JPC_ConvexHullShapeSettings_SetMaxErrorConvexRadius(JPC_ConvexHullShapeSettings *in_settings,
                                                    float in_max_err_convex_radius);
JPC_API float
JPC_ConvexHullShapeSettings_GetHullTolerance(const JPC_ConvexHullShapeSettings *in_settings);

JPC_API void
JPC_ConvexHullShapeSettings_SetHullTolerance(JPC_ConvexHullShapeSettings *in_settings,
                                             float in_hull_tolerance);
//--------------------------------------------------------------------------------------------------
//
// JPC_Shape
//
//--------------------------------------------------------------------------------------------------
JPC_API void
JPC_Shape_AddRef(JPC_Shape *in_shape);

JPC_API void
JPC_Shape_Release(JPC_Shape *in_shape);

JPC_API uint32_t
JPC_Shape_GetRefCount(const JPC_Shape *in_shape);

JPC_API JPC_ShapeType
JPC_Shape_GetType(const JPC_Shape *in_shape);

JPC_API JPC_ShapeSubType
JPC_Shape_GetSubType(const JPC_Shape *in_shape);

JPC_API uint64_t
JPC_Shape_GetUserData(const JPC_Shape *in_shape);

JPC_API void
JPC_Shape_SetUserData(JPC_Shape *in_shape, uint64_t in_user_data);
//--------------------------------------------------------------------------------------------------
//
// JPC_BodyInterface
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_Body *
JPC_BodyInterface_CreateBody(JPC_BodyInterface *in_iface, const JPC_BodyCreationSettings *in_setting);

JPC_API void
JPC_BodyInterface_DestroyBody(JPC_BodyInterface *in_iface, JPC_BodyID in_body_id);

JPC_API void
JPC_BodyInterface_AddBody(JPC_BodyInterface *in_iface, JPC_BodyID in_body_id, JPC_Activation in_mode);

JPC_API void
JPC_BodyInterface_RemoveBody(JPC_BodyInterface *in_iface, JPC_BodyID in_body_id);

JPC_API JPC_BodyID
JPC_BodyInterface_CreateAndAddBody(JPC_BodyInterface *in_iface,
                                   const JPC_BodyCreationSettings *in_settings,
                                   JPC_Activation in_mode);
JPC_API bool
JPC_BodyInterface_IsAdded(const JPC_BodyInterface *in_iface, JPC_BodyID in_body_id);

JPC_API void
JPC_BodyInterface_SetLinearVelocity(JPC_BodyInterface *in_iface,
                                    JPC_BodyID in_body_id,
                                    const float in_velocity[3]);
JPC_API void
JPC_BodyInterface_GetLinearVelocity(const JPC_BodyInterface *in_iface,
                                    JPC_BodyID in_body_id,
                                    float out_velocity[3]);
JPC_API void
JPC_BodyInterface_GetCenterOfMassPosition(const JPC_BodyInterface *in_iface,
                                          JPC_BodyID in_body_id,
                                          float out_position[3]);
JPC_API bool
JPC_BodyInterface_IsActive(const JPC_BodyInterface *in_iface, JPC_BodyID in_body_id);
//--------------------------------------------------------------------------------------------------
//
// JPC_Body
//
//--------------------------------------------------------------------------------------------------
JPC_API JPC_BodyID
JPC_Body_GetID(const JPC_Body *in_body);

JPC_API bool
JPC_Body_IsActive(const JPC_Body *in_body);

JPC_API bool
JPC_Body_IsStatic(const JPC_Body *in_body);

JPC_API bool
JPC_Body_IsKinematic(const JPC_Body *in_body);

JPC_API bool
JPC_Body_IsDynamic(const JPC_Body *in_body);

JPC_API bool
JPC_Body_CanBeKinematicOrDynamic(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetIsSensor(JPC_Body *in_body, bool in_is_sensor);

JPC_API bool
JPC_Body_IsSensor(const JPC_Body *in_body);

JPC_API JPC_MotionType
JPC_Body_GetMotionType(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetMotionType(JPC_Body *in_body, JPC_MotionType in_motion_type);

JPC_API JPC_BroadPhaseLayer
JPC_Body_GetBroadPhaseLayer(const JPC_Body *in_body);

JPC_API JPC_ObjectLayer
JPC_Body_GetObjectLayer(const JPC_Body *in_body);

JPC_API JPC_CollisionGroup *
JPC_Body_GetCollisionGroup(JPC_Body *in_body);

JPC_API void
JPC_Body_SetCollisionGroup(JPC_Body *in_body, const JPC_CollisionGroup *in_group);

JPC_API bool
JPC_Body_GetAllowSleeping(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetAllowSleeping(JPC_Body *in_body, bool in_allow_sleeping);

JPC_API float
JPC_Body_GetFriction(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetFriction(JPC_Body *in_body, float in_friction);

JPC_API float
JPC_Body_GetRestitution(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetRestitution(JPC_Body *in_body, float in_restitution);

JPC_API void
JPC_Body_GetLinearVelocity(const JPC_Body *in_body, float out_angular_velocity[3]);

JPC_API void
JPC_Body_SetLinearVelocity(JPC_Body *in_body, const float in_linear_velocity[3]);

JPC_API void
JPC_Body_SetLinearVelocityClamped(JPC_Body *in_body, const float in_linear_velocity[3]);

JPC_API void
JPC_Body_GetAngularVelocity(const JPC_Body *in_body, float out_angular_velocity[3]);

JPC_API void
JPC_Body_SetAnglularVelocity(JPC_Body *in_body, const float in_angular_velocity[3]);

JPC_API void
JPC_Body_SetAnglularVelocityClamped(JPC_Body *in_body, const float in_angular_velocity[3]);

JPC_API void
JPC_Body_GetPointVelocityCOM(const JPC_Body *in_body,
                             const float in_point_relative_to_com[3],
                             float out_velocity[3]);
JPC_API void
JPC_Body_GetPointVelocity(const JPC_Body *in_body, const float in_point[3], float out_velocity[3]);

JPC_API void
JPC_Body_AddForce(JPC_Body *in_body, const float in_force[3]);

JPC_API void
JPC_Body_AddForceAtPosition(JPC_Body *in_body, const float in_force[3], const float in_position[3]);

JPC_API void
JPC_Body_AddTorque(JPC_Body *in_body, const float in_torque[3]);

JPC_API void
JPC_Body_GetInverseInertia(const JPC_Body *in_body, float out_inverse_inertia[16]);

JPC_API void
JPC_Body_AddImpulse(JPC_Body *in_body, const float in_impulse[3]);

JPC_API void
JPC_Body_AddAngularImpulse(JPC_Body *in_body, const float in_angular_impulse[3]);

JPC_API void
JPC_Body_MoveKinematic(JPC_Body *in_body,
                       const float in_target_rotation[4],
                       float in_delta_time);
JPC_API void
JPC_Body_ApplyBuoyancyImpulse(JPC_Body *in_body,
                              const float in_plane[4],
                              float in_buoyancy,
                              float in_linear_drag,
                              float in_angular_drag,
                              const float in_fluid_velocity[3],
                              const float in_gravity[3],
                              float in_delta_time);
JPC_API bool
JPC_Body_IsInBroadPhase(const JPC_Body *in_body);

JPC_API bool
JPC_Body_IsCollisionCacheInvalid(const JPC_Body *in_body);

JPC_API const JPC_Shape *
JPC_Body_GetShape(const JPC_Body *in_body);

JPC_API void
JPC_Body_GetPosition(const JPC_Body *in_body, float out_position[3]);

JPC_API void
JPC_Body_GetRotation(const JPC_Body *in_body, float out_rotation[4]);

JPC_API void
JPC_Body_GetWorldTransform(const JPC_Body *in_body, float out_transform[16]);

JPC_API void
JPC_Body_GetCenterOfMassPosition(const JPC_Body *in_body, float out_position_com[3]);

JPC_API void
JPC_Body_GetInverseCenterOfMassTransform(const JPC_Body *in_body, float out_transform[16]);

JPC_API void
JPC_Body_GetWorldSpaceBounds(const JPC_Body *in_body, float out_min[3], float out_max[3]);

JPC_API JPC_MotionProperties *
JPC_Body_GetMotionProperties(JPC_Body *in_body);

JPC_API JPC_MotionProperties *
JPC_Body_GetMotionPropertiesUnchecked(JPC_Body *in_body);

JPC_API uint64_t
JPC_Body_GetUserData(const JPC_Body *in_body);

JPC_API void
JPC_Body_SetUserData(JPC_Body *in_body, uint64_t in_user_data);

JPC_API void
JPC_Body_GetWorldSpaceSurfaceNormal(const JPC_Body *in_body,
                                    const JPC_SubShapeID *in_sub_shape_id,
                                    const float in_position[3],
                                    float out_normal_vector[3]);
JPC_API void
JPC_Body_GetTransformedShape(const JPC_Body *in_body, JPC_TransformedShape *out_shape);

JPC_API void
JPC_Body_GetBodyCreationSettings(const JPC_Body *in_body, JPC_BodyCreationSettings *out_settings);
//--------------------------------------------------------------------------------------------------
//
// JPC_BodyID
//
//--------------------------------------------------------------------------------------------------
JPC_API uint32_t
JPC_BodyID_GetIndex(JPC_BodyID in_body_id);

JPC_API uint8_t
JPC_BodyID_GetSequenceNumber(JPC_BodyID in_body_id);

JPC_API bool
JPC_BodyID_IsInvalid(JPC_BodyID in_body_id);
//--------------------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
