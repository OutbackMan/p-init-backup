typedef unsigned int entity_index_t;

typedef struct {
	size_t num_components;
	size_t cap_components;

	BitArray* component_mask;

	DisplacementComponent* displacement_component;
} EntityManager;

status_code_t entity_manager__create_component_mask(BitArray* component_mask, const size_t num_components)
{
	for (size_t component_index = 0; component_index < starting_component_capacity; ++component_index) {
		bit_array_create(&component_mask[component_index]), starting_component_capacity);
	}
			
}

status_code_t entity_manager_create(EntityManager* entity_manager, const size_t starting_component_capacity)
{
	entity_manager->component_mask = calloc(sizeof(BitArray), starting_component_capacity);

	for (size_t component_index = 0; component_index < starting_component_capacity; ++component_index) {
		bit_array_create(&(entity_manager->component_mask[component_index]), starting_component_capacity);
	}

	entity_manager->num_components = 0;
	entity_manager->cap_components = starting_component_capacity;

	entity_manager->displacement_component = calloc(sizeof(DisplacementComponent), starting_component_capacity); 
}

void entity_manager_destroy(EntityManager* entity_manager)
{
	for (size_t component_index = 0; component_index < starting_component_capacity; ++component_index) {
		bit_array_free(&(entity_manager->component_mask[component_index]), starting_component_capacity);
	}
	
	bit_array_free(entity_manager->component_mask);	

	free(entity_manager->displacement_component);
}

entity_index_t entity_manager_create_entity(EntityManager* entity_manager)
{
	unsigned entity = 0;

	for (unsigned entity_index = 0; entity_index < ; ++entity_index) {
		if (bit_array_get(entity_manager->component_mask, entity_index) == COMPONENT_NONE) {
			return entity_index;	
		}
	}

	// no entities left
	return entity;
}
