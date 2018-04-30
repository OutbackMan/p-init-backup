typedef unsigned int entity_index_t;

typedef struct {
	size_t num_components;
	size_t cap_components;

	BitArray* component_mask;

	DisplacementComponent* displacement_component;
} EntityManager;

int main(void)
{
	EntityManager entity_manager = {0};	
	game__entity_manager_create(&entity_manager, 30);
}

GAME_STATUS game__entity_manager_create(EntityManager* entity_manager, const size_t starting_component_capacity)
{
	BitArray bit_array_temp = GAME_DEFAULT_INITIALISER;
	if (bit_array_create(&bit_array_temp, starting_component_capacity) != SUCCESS) {
		GAME_LEAVE(FAILURE);		
	}

	for (size_t component_index = 0; component_index < starting_component_capacity; ++component_index) {
		GAME_STRETCHY_BUF_PUSH(entity_manager->component_mask, bit_array_temp);
		GAME_STRETCHY_BUF_PUSH(entity_manager->displacement_component, GAME_DEFAULT_INITIALISER); 
	}

	entity_manager->num_components = 0;
	entity_manager->cap_components = starting_component_capacity;

}

void entity_manager_destroy(EntityManager* entity_manager)
{
	for (size_t component_index = 0; component_index < STRETCHY_BUF_LEN(entity_manager->component_mask); ++component_index) {
		bit_array_free(&(entity_manager->component_mask[component_index]), starting_component_capacity);
	}

	GAME_STRETCHY_BUF_FREE(entity_manager->component_mask);
	GAME_STRETCHY_BUF_FREE(entity_manager->displacement);
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
